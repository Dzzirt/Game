
template< class T > void SafeDelete(T*& pVal) {
	delete pVal;
	pVal = NULL;
}