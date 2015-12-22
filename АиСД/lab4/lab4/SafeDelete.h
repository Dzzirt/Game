
template<typename T> void SafeDelete(T*& a) {
	delete a;
	a = NULL;
}