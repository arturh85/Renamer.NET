#ifndef PROPERTY_OBJECT
#define PROPERTY_OBJECT

//! generic Interface for user manipulatable Objects
class PropertyObject {
	public:
        //---------------------------------------------------------------------
        //  constructors
		PropertyObject() {};
		virtual ~PropertyObject() {};

        //---------------------------------------------------------------------
        //  methodes

        //! get a pointer from an object
        /**
            The calling process is responsible for deleting it.
        */
        virtual PropertyObject* toPropertyObjectPtr() const = 0;
        //virtual PropertyObject* clone() {};

        void foo() {};

	protected:

	private:

};


#endif // PROPERTY_OBJECT

