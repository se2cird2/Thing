#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <objc/runtime.h>

// Hook function prototypes
void __fastcall didPickDocumentAtURL(void *a1, void *a2, void *a3,
    void (__fastcall *a4)(id, const char *, id, NSURL *));
void __fastcall didPickDocumentAtURLs(void *a1, void *a2, void *a3,
    void (__fastcall *a4)(id, const char *, id, id));
id __fastcall initWithDocumentTypesInMode(void *a1, void *a2, 
    __int64 a3, __int64 (__fastcall *a4)(id, const char *, id, _QWORD));
id __fastcall initForOpeningContentTypesAsCopy(void *a1, void *a2, 
    char a3, __int64 (__fastcall *a4)(id, const char *, id, __int64));
void __fastcall setDelegate(void *a1, void *a2, void (__fastcall *a3)(id, const char *, id));
void __fastcall swizzle_documentPicker(objc_class *a1);
void swizzleNSURL(void);
void init();
id temperoryDirectory(void);
void initHooks(void);

// Utility
NSURL *__fastcall moveFileToTemp(void *a1, void *a2);