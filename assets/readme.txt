//---- Add environment variable:
name: wxWidgets_ROOT_DIR
path: D:\install\libs\wxwidgets\wxWidgets_lib\wxWidgets-3.1.0

//---- wxInclude usage example:
wxInclude.exe --const --input-type=.png --appendtype --output-file=Images.h

Change:
	inline wxImage _wxConvertMemoryToImage(const unsigned char* data, int length, -->> long type <<-- = wxBITMAP_TYPE_ANY)
to:
	inline wxImage _wxConvertMemoryToImage(const unsigned char* data, int length, -->> wxBitmapType type <<-- = wxBITMAP_TYPE_ANY)
