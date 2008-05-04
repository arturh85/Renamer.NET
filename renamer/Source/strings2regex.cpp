#include "strings2regex.h"
using boost::regex;
using boost::smatch;

string escapeRegex(string s);

struct part {
	//string sRegex;
	string text;
	size_t index;
	bool isRegex;
};

boost::regex string2regex(string s1, string s2) {
    Logger logger = Logger::getInstance("string2regex");
    LOG4CPLUS_TRACE(logger, "s1 = " << s1);
    LOG4CPLUS_TRACE(logger, "s2 = " << s2);

    part myPart;
    myPart.text = s1;
    myPart.isRegex = false;
    myPart.index = 0;

    typedef list<part> parts_t;
    parts_t myParts;
    myParts.push_front(myPart);
//    refine(myParts, s2);

    bool fDivdeable = true;
    size_t index = 99999;
    while (fDivdeable) {

    	for (parts_t::iterator itPart = myParts.begin(); itPart!=myParts.end(); itPart++) {
            LOG4CPLUS_TRACE(logger, "part = " << (itPart->isRegex? "* " : "  ")  << itPart->text);
    	}

        LOG4CPLUS_TRACE(logger, "part count = " << myParts.size());

        for (parts_t::iterator itEvalPart = myParts.begin(); itEvalPart!=myParts.end(); itEvalPart++) {
            LOG4CPLUS_TRACE(logger, "part = " << itEvalPart->text);

            if (!itEvalPart->isRegex) {
                string sTestRegex = "^";
                bool fTrailingWildcard = false;

                for (parts_t::iterator itPreviousPart = myParts.begin();
                     itPreviousPart!=myParts.end();
                     itPreviousPart++) {

                    if (itPreviousPart->index == itEvalPart->index) {
                        sTestRegex += escapeRegex(itEvalPart->text);
                        fTrailingWildcard = false;

                    } else if (itPreviousPart->isRegex) {
                        sTestRegex += itPreviousPart->text;
                        fTrailingWildcard = false;

                    } else if (!fTrailingWildcard) {
                        sTestRegex += ".+";
                        fTrailingWildcard=true;
                        //sTestRegex += escapeRegex(itPreviousPart->text);
                    }

                }

//                if (itEvalPart->index < myParts.size()-1 && !fTrailingWildcard ) {
//                    sTestRegex += ".*";
//                }

                sTestRegex += "$";
                LOG4CPLUS_TRACE(logger, "sTestRegex = " << sTestRegex);
                if (regex_match(s2,regex(sTestRegex))) {
                    itEvalPart->text = escapeRegex(itEvalPart->text);
                    itEvalPart->isRegex = true;
                }

            }
        }

    	/// split all unmatched parts in half
    	fDivdeable = false;
    	parts_t newPartsList;
        index = 0;
    	for (parts_t::iterator itPart = myParts.begin(); itPart!=myParts.end(); itPart++) {
    	    if (itPart->isRegex || itPart->text.size() == 1) {
    	        itPart->index = index++;
    	    	newPartsList.push_back(*itPart);
    	    } else {
    	        fDivdeable =true;

    	    	size_t middle = itPart->text.size()/2;
    	    	part leftPart;
    	    	leftPart.isRegex = false;
    	    	leftPart.index = index++;
    	    	leftPart.text = itPart->text.substr(0, middle);
    	    	newPartsList.push_back(leftPart);

    	    	part rightPart;
    	    	rightPart.isRegex = false;
    	    	rightPart.index = index++;
    	    	rightPart.text = itPart->text.substr(middle);
    	    	newPartsList.push_back(rightPart);
    	    }
    	}
    	myParts = newPartsList;
    }

    /// reduce number of parts to a minum
    for (parts_t::iterator itPart = myParts.begin(); itPart!=myParts.end(); itPart++) {
        LOG4CPLUS_TRACE(logger, "part = " << (itPart->isRegex? "* " : "  ")  << itPart->text);
    }

    parts_t minParts;
    part* partToAdd = NULL;
    index = 0;
    for (parts_t::iterator itPart = myParts.begin()++; itPart!=myParts.end(); itPart++) {
        if (!partToAdd) {
        	partToAdd = new part(*itPart);
        	partToAdd->index = index++;

        } else if (itPart->isRegex == partToAdd->isRegex) {
            if (itPart->isRegex) {
                partToAdd->text += itPart->text;
            }

        } else {
            minParts.push_back(*partToAdd);
            partToAdd->isRegex = itPart->isRegex;
            partToAdd->index = index++;
            if (itPart->isRegex) {
                partToAdd->text = itPart->text;

            } else {
                partToAdd->text = "(.+)";

            }
        }
    }
    minParts.push_back(*partToAdd);
    delete partToAdd;

    /// determine character class of wildcards (e.g. non regex parts)
    for (parts_t::iterator itEvalWildcard = minParts.begin()++; itEvalWildcard!=minParts.end();
         itEvalWildcard++) {

        if (!itEvalWildcard->isRegex) {

            string sRegex = "^";
            for (parts_t::iterator itPart = minParts.begin()++; itPart!=minParts.end(); itPart++) {
                if (itEvalWildcard->index == itPart->index) {
                	sRegex += "(\\d+)";
                } else {
                	sRegex += itPart->text;
                }
            }
            sRegex += "$";
            LOG4CPLUS_TRACE(logger, "sRegex = " << sRegex);
            if (regex_match(s1,regex(sRegex)) && regex_match(s2,regex(sRegex))) {
                itEvalWildcard->text = "(\\d+)";
            }

        }
    }

    ///build regex
    string sRetVal = "^";
    for (parts_t::iterator itPart = minParts.begin()++; itPart!=minParts.end(); itPart++) {
        sRetVal += itPart->text;
    }
    sRetVal += "$";
    LOG4CPLUS_INFO(logger, "sRetVal = " << sRetVal);
    return regex(sRetVal);
}

#ifdef RENAMER_UNIT_TEST
void testFiles(string s1, string s2) {
  regex retVal = string2regex(s1,s2);
  BOOST_CHECK_MESSAGE(regex_match(s1, retVal),s1);
  BOOST_CHECK_MESSAGE(regex_match(s2, retVal),s2);
}

void test_string2regex() {
    testFiles("The.Unit.S02E17.HDTV.XviD-XOR",
              "The.Unit.S02E21.HDTV.XviD-XOR");

    testFiles("14Dr.House.S02E14.Sex.wird.unterschaetzt.German.Dubbed.DVDRIP.WS.XviD-TvR",
              "16Dr.House.S02E16.Sicher.genug.German.Dubbed.DVDRIP.WS.XviD-TvR");

    testFiles("The.Simpsons.S18E16.PDTV.XviD-LOL",
              "The.Simpsons.S18E13.PDTV.XviD-2HD");

    testFiles("The.Sci.Fi.Guys.S01.Ep7.Listeners.Choice.Show",
              "The.Sci.Fi.Guys.S01.Ep3.Chuck.Campbell");

    testFiles("Battlestar Galactica [1x12] Kobol's Last Gleaming Part 1",
              "Battlestar Galactica [1x09] Secrets And Lies");

    testFiles("The.Unit.S02E22.Freefall.HDTV.XviD-FQM.avi",
              "The.Simpsons.S18E16.PDTV.XviD-LOL.avi");

//    testFiles("",
//              "");

}
#endif

string escapeRegex(string s) {
  string retVal(s);
  boost::algorithm::replace_all(retVal, ".", "\\.");
  boost::algorithm::replace_all(retVal, "[", "\\[");
  boost::algorithm::replace_all(retVal, "]", "\\]");
  boost::algorithm::replace_all(retVal, "(", "\\(");
  boost::algorithm::replace_all(retVal, ")", "\\)");

  return retVal;
}
