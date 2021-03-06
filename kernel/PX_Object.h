#ifndef PIXELSES_OBJECT_H
#define PIXELSES_OBJECT_H

#include "../core/PX_Core.h"
#include "PX_Animation.h"
#include "PX_Partical.h"


//////////////////////////////////////////////////////////////////////////
/// Common Events
//////////////////////////////////////////////////////////////////////////
#define PX_OBJECT_EVENT_ANY					0
#define PX_OBJECT_EVENT_CURSORMOVE			1
#define PX_OBJECT_EVENT_CURSORUP			2
#define PX_OBJECT_EVENT_CURSORRDOWN			3
#define PX_OBJECT_EVENT_CURSORDOWN			4
#define PX_OBJECT_EVENT_CURSORRUP			5
#define PX_OBJECT_EVENT_CURSOROVER			6
#define PX_OBJECT_EVENT_CURSOROUT			7
#define PX_OBJECT_EVENT_CURSORWHEEL         8
#define PX_OBJECT_EVENT_CURSORCLICK			9
#define PX_OBJECT_EVENT_CURSORDRAG			10
#define PX_OBJECT_EVENT_STRING				11
#define PX_OBJECT_EVENT_EXECUTE				12
#define PX_OBJECT_EVENT_VALUECHANGED		13
#define PX_OBJECT_EVENT_DRAGFILE			14
#define PX_OBJECT_EVENT_KEYDOWN				15
#define PX_OBJECT_EVENT_IMPACT				16
#define PX_OBJECT_EVENT_ONFOCUSCHANGED		17
#define PX_OBJECT_EVENT_SCALE               18
#define PX_OBJECT_EVENT_WINDOWRESIZE        19
#define PX_OBJECT_EVENT_ONFOCUS				20
#define PX_OBJECT_EVENT_LOSTFOCUS           21


//////////////////////////////////////////////////////////////////////////////
//    Type of Controls
/////////////////////////////////////////////////////////////////////////////

enum PX_OBJECT_TYPE
{
  PX_OBJECT_TYPE_NULL			,
  PX_OBJECT_TYPE_LABEL			,
  PX_OBJECT_TYPE_PROCESSBAR		,
  PX_OBJECT_TYPE_IMAGE			,
  PX_OBJECT_TYPE_PARTICAL		,
  PX_OBJECT_TYPE_SLIDERBAR		,
  PX_OBJECT_TYPE_LIST			,
  PX_OBJECT_TYPE_LISTITEM		,
  PX_OBJECT_TYPE_PUSHBUTTON		,
  PX_OBJECT_TYPE_EDIT           ,
  PX_OBJECT_TYPE_SCROLLAREA     ,
  PX_OBJECT_TYPE_AUTOTEXT		,
  PX_OBJECT_TYPE_ANIMATION		,
  PX_OBJECT_TYPE_CURSORBUTTON   ,
  PX_OBJECT_TYPE_VKEYBOARD		,
  PX_OBJECT_TYPE_VNKEYBOARD		,
  PX_OBJECT_TYPE_COORDINATE     ,
  PX_OBJECT_TYPE_FILTEREDITOR   ,
  PX_OBJECT_TYPE_CHECKBOX		,
  PX_OBJECT_TYPE_ROTATION		,
  PX_OBJECT_TYPE_MENU			,
  PX_OBJECT_TYPE_SELECTBAR		,
  PX_OBJECT_TYPE_RADIOBOX		,
  PX_OBJECT_TYPE_EXPLORER		,
};


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////



#define  PX_OBJECT_IMAGE_LISTITEM_STYLE_NONE		0
#define  PX_OBJECT_IMAGE_LISTITEM_STYLE_BORDER		1

#define  PX_OBJECT_IMAGE_LISTBOX_ITEMHEIGHT			18
#define  PX_OBJECT_IMAGE_LISTBOX_SLIDERWITDH		8

#define  PX_OBJECT_IMAGE_LISTBOX_STYLE_ITEMBORDER	1
#define  PX_OBJECT_IMAGE_LISTBOX_STYLE_SELECT		2








#define  PX_OBJECT_FILTEREDITOR_DEFAULE_HORIZONTALPIXELDIVIDING 48
#define  PX_OBJECT_FILTEREDITOR_DEFAULE_VERTICALPIXELDIVIDING   20
#define	 PX_OBJECT_FILTEREDITOR_DEFAULT_FRAMELINE_WIDTH			   2


///////////////////////////////////////////////////////////////////////////
////  PixelsES Object
//////////////////////////////////////////////////////////////////////////
struct _PX_Object;
typedef struct _PX_Object PX_Object;

typedef px_void  (*Function_ObjectUpdate)(PX_Object *,px_uint elpased);
typedef px_void  (*Function_ObjectBeginRender)(px_surface *,PX_Object *,px_dword);
typedef px_void  (*Function_ObjectRender)(px_surface *psurface,PX_Object *,px_uint elpased);
typedef px_void  (*Function_ObjectEndRender)(px_surface *,PX_Object *,px_dword);
typedef px_void  (*Function_ObjectFree)(PX_Object *);
typedef px_void  (*Function_ObjectLinkChild)(PX_Object *parent,PX_Object *child);

struct _PX_Object
{
	px_int id;
	px_float x;
	px_float y;
	px_float z;
	px_float Width;
	px_float Height;
	px_float Length;
	px_float diameter;//if the member is not zero,The Object is round shape
	px_bool OnFocus;
	px_bool OnLostFocusReleaseEvent;
	px_bool Enabled;
	px_bool Visible;
	px_bool ReceiveEvents;
	px_int	Type;
	union
	{
	px_int  User_int;
	px_void *User_ptr;
	};
	px_int   world_index;
	px_dword impact_Object_type;
	px_dword impact_test_type;
	px_void *pObject;
	px_memorypool *mp;
	struct _PX_Object *pChilds;
	struct _PX_Object *pParent;
	struct _PX_Object *pPreBrother;
	struct _PX_Object *pNextBrother;

	struct _PX_Object_EventAction *pEventActions; 
	Function_ObjectUpdate Func_ObjectUpdate;
	Function_ObjectRender Func_ObjectRender;
	Function_ObjectFree   Func_ObjectFree;
	Function_ObjectLinkChild Func_ObjectLinkChild;
	Function_ObjectBeginRender Func_ObjectBeginRender;
	Function_ObjectEndRender Func_ObjectEndRender;
};


//////////////////////////////////////////////////////////////////////////
///   Controllers
//////////////////////////////////////////////////////////////////////////




typedef struct 
{
	PX_ALIGN Align;
	PX_Animation animation;
}PX_Object_Animation;




typedef struct
{
	px_shape *shape;
	px_point cursorPoint;
	px_color blendColor;
}PX_Object_RoundCursor;



typedef struct _PX_Object_Event
{
	px_uint Event;
	union
	{
		px_char Param_char[16];
		px_uint Param_uint[4];
		px_int Param_int[4];
		px_float Param_float[4];
		px_void *Param_ptr[4];
		px_bool Param_bool[4];
	};
}PX_Object_Event;

//////////////////////////////////////////////////////////////////////////
//EVENT params
PX_Object_Event PX_Object_Event_CursorOffset(PX_Object_Event e,px_point offset);

px_float PX_Object_Event_GetCursorX(PX_Object_Event e);
px_float PX_Object_Event_GetCursorY(PX_Object_Event e);
px_float PX_Object_Event_GetCursorZ(PX_Object_Event e);
px_int PX_Object_Event_GetCursorIndex(PX_Object_Event e);

px_float PX_Object_Event_GetWidth(PX_Object_Event e);
px_float PX_Object_Event_GetHeight(PX_Object_Event e);
px_int PX_Object_Event_GetIndex(PX_Object_Event e);

px_void PX_Object_Event_SetWidth(PX_Object_Event *e,px_float w);
px_void PX_Object_Event_SetHeight(PX_Object_Event *e,px_float h);
px_void PX_Object_Event_SetCursorX(PX_Object_Event *e,px_float x);
px_void PX_Object_Event_SetCursorY(PX_Object_Event *e,px_float y);
px_void PX_Object_Event_SetCursorZ(PX_Object_Event *e,px_float z);
px_void PX_Object_Event_SetCursorIndex(PX_Object_Event *e,px_int index);

px_float PX_Object_Event_GetScaleCursorX(PX_Object_Event e);
px_float PX_Object_Event_GetScaleCursorY(PX_Object_Event e);
px_float PX_Object_Event_GetScaleCursorZ(PX_Object_Event e);

px_void PX_Object_Event_SetScaleCursorX(PX_Object_Event *e,px_float x);
px_void PX_Object_Event_SetScaleCursorY(PX_Object_Event *e,px_float y);
px_void PX_Object_Event_SetScaleCursorZ(PX_Object_Event *e,px_float z);

px_uint PX_Object_Event_GetKeyDown(PX_Object_Event e);
px_void PX_Object_Event_SetKeyDown(PX_Object_Event *e,px_uint key);
px_char* PX_Object_Event_GetStringPtr(PX_Object_Event e);
px_void* PX_Object_Event_GetDataPtr(PX_Object_Event e);
px_void PX_Object_Event_SetStringPtr(PX_Object_Event *e,px_void *ptr);
px_void PX_Object_Event_SetDataPtr(PX_Object_Event *e,px_void *ptr);
px_void PX_Object_Event_SetIndex(PX_Object_Event *e,px_int index);
struct _PX_Object_EventAction
{
	px_uint EventAction;
	px_void (*EventActionFunc)(PX_Object *,PX_Object_Event e,px_void *user_ptr);
	px_void *user_ptr;
	struct _PX_Object_EventAction *pNext;
	struct _PX_Object_EventAction *pPre;
};

typedef struct _PX_Object_EventAction PX_OBJECT_EventAction;


PX_Object *PX_ObjectCreate(px_memorypool *mp,PX_Object *Parent,px_float x,px_float y,px_float z,px_float Width,px_float Height,px_float Lenght);
PX_Object *PX_ObjectCreateEx(px_memorypool *mp,PX_Object *Parent,\
	px_float x,px_float y,px_float z,px_float Width,px_float Height,px_float Lenght,\
	px_int type,\
	Function_ObjectUpdate Func_ObjectUpdate,\
	Function_ObjectRender Func_ObjectRender,\
	Function_ObjectFree   Func_ObjectFree,\
	px_void *desc,\
	px_int size
	);
px_void    PX_ObjectGetInheritXY(PX_Object *Object,px_float *x,px_float *y);
px_void	   PX_ObjectInit(px_memorypool *mp,PX_Object *Object,PX_Object *Parent,px_float x,px_float y,px_float z,px_float Width,px_float Height,px_float Lenght);
px_void    PX_ObjectSetUserCode(PX_Object *pObject,px_int user_int);
px_void    PX_ObjectSetUserPointer(PX_Object *pObject,px_void *user_ptr);
px_void    PX_ObjectDelete(PX_Object *pObject);
px_void	   PX_ObjectDeleteChilds( PX_Object *pObject );
px_void	   PX_ObjectSetPosition(PX_Object *Object,px_float x,px_float y,px_float z);
px_void    PX_ObjectSetSize(PX_Object *Object,px_float Width,px_float Height,px_float length);
px_void	   PX_ObjectSetVisible(PX_Object *Object,px_bool visible);
PX_Object  *PX_ObjectGetChild(PX_Object *Object,px_int Index);
px_void     PX_ObjectSetFocus(PX_Object *Object);
px_void     PX_ObjectClearFocus(PX_Object *Object);
px_bool		PX_ObjectIsPointInRegion(PX_Object *Object,px_float x,px_float y);
px_bool		PX_ObjectIsCursorInRegion(PX_Object *Object,PX_Object_Event e);
px_float	PX_ObjectGetHeight(PX_Object *Object);
px_float	PX_ObjectGetWidth(PX_Object *Object);

px_void PX_ObjectUpdate(PX_Object *Object,px_uint elpased );
px_void PX_ObjectRender(px_surface *pSurface,PX_Object *Object,px_uint elpased);

px_int PX_ObjectRegisterEvent(PX_Object *Object,px_uint Event,px_void (*ProcessFunc)(PX_Object *,PX_Object_Event e,px_void *user_ptr),px_void *ptr);
px_void PX_ObjectPostEvent(PX_Object *pPost,PX_Object_Event Event);
px_void PX_ObjectExecuteEvent(PX_Object *pPost,PX_Object_Event Event);

//////////////////////////////////////////////////////////////////////////
//Label
//////////////////////////////////////////////////////////////////////////

typedef enum
{
	PX_OBJECT_LABEL_STYLE_RECT,
	PX_OBJECT_LABEL_STYLE_ROUNDRECT,
}PX_OBJECT_LABEL_STYLE;

typedef struct  
{
	PX_ALIGN Align;
	px_color borderColor;
	px_color TextColor;
	px_color BackgroundColor;
	px_bool  bBorder;
	PX_OBJECT_LABEL_STYLE style;
	PX_FontModule *fontModule;
	px_char *Text;
}PX_Object_Label;

PX_Object *	PX_Object_LabelCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,const px_char *Text,PX_FontModule *fm,px_color Color);
PX_Object_Label  *	PX_Object_GetLabel(PX_Object *Object);
px_char	  * PX_Object_LabelGetText(PX_Object *Label);
px_void		PX_Object_LabelSetText(PX_Object *pLabel,const px_char *Text);
px_void		PX_Object_LabelSetTextColor(PX_Object *pLabel,px_color Color);
px_void		PX_Object_LabelSetBackgroundColor(PX_Object *pLabel,px_color Color);
px_void		PX_Object_LabelSetAlign(PX_Object *pLabel,PX_ALIGN Align);
px_void		PX_Object_LabelSetBorder(PX_Object *pLabel,px_bool b);
px_void		PX_Object_LabelSetBorderColor(PX_Object *pLabel,px_color color);
px_void		PX_Object_LabelSetStyle(PX_Object *pLabel,PX_OBJECT_LABEL_STYLE style);
//////////////////////////////////////////////////////////////////////////
//ProcessBar
//////////////////////////////////////////////////////////////////////////
typedef struct 
{
	px_int Value;
	px_int MAX;
	px_color Color;
	px_color BackgroundColor;
}PX_Object_ProcessBar;

PX_Object *	PX_Object_ProcessBarCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height);
PX_Object_ProcessBar *PX_Object_GetProcessBar(PX_Object *Object);
px_void		PX_Object_ProcessBarSetColor(PX_Object *pProcessBar,px_color Color);
px_void		PX_Object_ProcessBarSetBackgroundColor(PX_Object *pProcessBar,px_color Color);
px_void		PX_Object_ProcessBarSetValue(PX_Object *pProcessBar,px_int Value);
px_void		PX_Object_ProcessBarSetMax(PX_Object *pProcessBar,px_int Max);
px_int		PX_Object_ProcessBarGetValue(PX_Object *pProcessBar);


//////////////////////////////////////////////////////////////////////////
//Image
//////////////////////////////////////////////////////////////////////////

typedef struct 
{
	PX_ALIGN Align;
	px_texture *pTexture;
	px_texture *pmask;
}PX_Object_Image;

PX_Object * PX_Object_ImageCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int width,px_int height,px_texture *ptex );
PX_Object_Image *PX_Object_GetImage(PX_Object *Object);
px_void	   PX_Object_ImageSetAlign(PX_Object *pObject,PX_ALIGN Align);
px_void	   PX_Object_ImageSetMask(PX_Object *pObject,px_texture *pmask);
px_void    PX_Object_ImageSetTexture(PX_Object *pObject,px_texture *pTex);
px_void	   PX_Object_ImageFreeWithTexture(PX_Object *pObject);

//////////////////////////////////////////////////////////////////////////
//SliderBar
//////////////////////////////////////////////////////////////////////////

typedef enum 
{
	PX_OBJECT_SLIDERBAR_TYPE_HORIZONTAL		,
	PX_OBJECT_SLIDERBAR_TYPE_VERTICAL		,
}PX_OBJECT_SLIDERBAR_TYPE;

typedef enum  
{
	PX_OBJECT_SLIDERBAR_STYLE_BOX			,
	PX_OBJECT_SLIDERBAR_STYLE_LINER			,
}PX_OBJECT_SLIDERBAR_STYLE;

typedef enum 
{
	PX_OBJECT_SLIDERBAR_STATUS_ONDRAG		,
	PX_OBJECT_SLIDERBAR_STATUS_NORMAL		,
}PX_OBJECT_SLIDERBAR_STATUS;


typedef struct 
{
	PX_OBJECT_SLIDERBAR_TYPE Type;
	PX_OBJECT_SLIDERBAR_STYLE style;
	PX_OBJECT_SLIDERBAR_STATUS status;
	px_float btnDownX,btnDownY;
	px_float DargButtonX,DargButtonY;
	px_int Min;
	px_int Max;
	px_int lastValue;
	px_int Value;
	px_int SliderButtonLength;
	px_color color;
	px_color BackgroundColor;
}PX_Object_SliderBar;

PX_Object *PX_Object_SliderBarCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,PX_OBJECT_SLIDERBAR_TYPE Type,PX_OBJECT_SLIDERBAR_STYLE style);
PX_Object_SliderBar *PX_Object_GetSliderBar(PX_Object *Object);
px_void	   PX_Object_SliderBarSetValue(PX_Object *pSliderBar,px_int Value);
px_void	   PX_Object_SliderBarSetRange(PX_Object *pSliderBar,px_int Min,px_int Max);
px_int	   PX_Object_SliderBarGetMax( PX_Object *pSliderBar );
px_int	   PX_Object_SliderBarGetValue(PX_Object *pSliderBar);
px_void	   PX_Object_SliderBarRender(px_surface *psurface,PX_Object *pSliderBar,px_uint elpased);
px_void    PX_Object_SliderBarSetBackgroundColor(PX_Object *pSliderBar,px_color color);
px_void	   PX_Object_SliderBarFree(PX_Object *pSliderBar);
px_void    PX_Object_SliderBarSetColor(PX_Object *pSliderBar,px_color color);
px_void	   PX_Object_SliderBarSetSliderButtonLength(PX_Object *pSliderBar,px_int length);


//////////////////////////////////////////////////////////////////////////
//PushButton
//////////////////////////////////////////////////////////////////////////

#define PX_OBJECT_PUSHBUTTON_ROUNDRADIUS 8.0f
typedef enum
{
	PX_OBJECT_BUTTON_STATE_ONCURSOR,
	PX_OBJECT_BUTTON_STATE_ONPUSH,
	PX_OBJECT_BUTTON_STATE_NORMAL,
}PX_Object_PUSHBUTTON_STATE;


typedef enum
{
	PX_OBJECT_PUSHBUTTON_STYLE_RECT,
	PX_OBJECT_PUSHBUTTON_STYLE_ROUNDRECT,
}PX_OBJECT_PUSHBUTTON_STYLE;

typedef struct 
{
	px_bool Border;
	px_color TextColor;
	px_color BorderColor;
	px_color BackgroundColor;
	px_color CursorColor;
	px_color PushColor;
	px_char *Text;
	PX_FontModule *fontModule;
	px_texture *Texture;
	px_shape *shape;
	px_float roundradius;
	PX_OBJECT_PUSHBUTTON_STYLE style;
	PX_Object_PUSHBUTTON_STATE state;
}PX_Object_PushButton;

PX_Object *PX_Object_PushButtonCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,const px_char *Text,PX_FontModule *fontmodule,px_color Color);
PX_Object_PushButton * PX_Object_GetPushButton( PX_Object *Object );
px_char * PX_Object_PushButtonGetText( PX_Object *PushButton );
px_void PX_Object_PushButtonSetText( PX_Object *pObject,const px_char *Text );
px_void PX_Object_PushButtonSetBackgroundColor( PX_Object *pObject,px_color Color );
px_void PX_Object_PushButtonSetCursorColor( PX_Object *pObject,px_color Color );
px_void PX_Object_PushButtonSetStyle(PX_Object *pObject,PX_OBJECT_PUSHBUTTON_STYLE style);
px_void PX_Object_PushButtonSetPushColor( PX_Object *pObject,px_color Color );
px_void PX_Object_PushButtonSetBorderColor( PX_Object *pObject,px_color Color );
px_void PX_Object_PushButtonSetBorder( PX_Object *Object,px_bool Border );
px_void PX_Object_PushButtonRender(px_surface *psurface, PX_Object *pObject,px_uint elpased);
px_void PX_Object_PushButtonSetTextColor( PX_Object *pObject,px_color Color );
px_void PX_Object_PushButtonSetTexture(PX_Object *pObject,px_texture *texture);
px_void PX_Object_PushButtonSetShape(PX_Object *pObject,px_shape *pshape);
px_void PX_Object_PushButtonFree( PX_Object *Obj );

//////////////////////////////////////////////////////////////////////////
//Edit
//////////////////////////////////////////////////////////////////////////
typedef enum
{
	PX_OBJECT_EDIT_STATE_ONCURSOR,
	PX_OBJECT_EDIT_STATE_NORMAL,
}PX_OBJECT_EDIT_STATE;

typedef enum
{
	PX_OBJECT_EDIT_STYLE_RECT,
	PX_OBJECT_EDIT_STYLE_ROUNDRECT,
}PX_OBJECT_EDIT_STYLE;

typedef struct 
{
	px_string text;
	px_bool onFocus;
	px_bool Border;
	px_color TextColor;
	px_color BorderColor;
	px_color CursorColor;
	px_color BackgroundColor;
	px_uint elpased;
	px_bool Password;
	px_bool AutoNewline;
	px_int AutoNewLineSpacing;
	px_int XOffset,YOffset;
	px_int VerticalOffset,HorizontalOffset;
	px_int xFontSpacing,yFontSpacing;
	px_int cursor_index;
	px_int max_length;
	px_surface EditSurface;
	PX_FontModule *fontModule;
	px_char Limit[128];
	PX_OBJECT_EDIT_STATE state;
	PX_OBJECT_EDIT_STYLE style;
}PX_Object_Edit;

PX_Object* PX_Object_EditCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,PX_FontModule *fontModule,px_color TextColor );
PX_Object_Edit * PX_Object_GetEdit( PX_Object *Object );
px_char * PX_Object_EditGetText( PX_Object *pObject );
px_void PX_Object_EditSetMaxTextLength(PX_Object *pObject,px_int max_length);
px_void PX_Object_EditSetText( PX_Object *pObject,const px_char *Text );
px_void PX_Object_EditAppendText( PX_Object *pObject,const px_char *Text );
px_void PX_Object_EditSetFocus( PX_Object *pObject,px_bool OnFocus);
px_void PX_Object_EditSetPasswordStyle( PX_Object *pObject,px_uchar Enabled );
px_void PX_Object_EditSetBackgroundColor( PX_Object *pObject,px_color Color );
px_void PX_Object_EditSetBorderColor( PX_Object *pObject,px_color Color );
px_void PX_Object_EditSetCursorColor( PX_Object *pObject,px_color Color );
px_void PX_Object_EditSetTextColor( PX_Object *pObject,px_color Color );
px_void PX_Object_EditSetLimit(PX_Object *pObject,const px_char *Limit);
px_void PX_Object_EditSetStyle(PX_Object *pObject,PX_OBJECT_EDIT_STYLE style);
px_void PX_Object_EditSetBorder( PX_Object *pObj,px_bool Border );
px_void PX_Object_EditRender(px_surface *psurface, PX_Object *pObject,px_uint elpased);
px_void PX_Object_EditFree( PX_Object *pObject );
px_void PX_Object_EditAddString(PX_Object *pObject,px_char *Text);
px_void PX_Object_EditBackspace(PX_Object *pObject);
px_void PX_Object_EditAutoNewLine(PX_Object *pObject,px_bool b,px_int AutoNewLineSpacing);
px_void PX_Object_EditSetOffset(PX_Object *pObject,px_int TopOffset,px_int LeftOffset);

/////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	px_bool bBorder;
	px_surface surface;
	px_color BackgroundColor;
	px_color borderColor;
	PX_Object *root;
	PX_Object *hscroll,*vscroll;
}PX_Object_ScrollArea;


PX_Object *PX_Object_ScrollAreaCreate(px_memorypool *mp,PX_Object *Parent,int x,int y,int height,int width);
PX_Object_ScrollArea * PX_Object_GetScrollArea( PX_Object *Object );
PX_Object * PX_Object_ScrollAreaGetIncludedObjects(PX_Object *pObj);
px_void PX_Object_ScrollAreaMoveToBottom(PX_Object *pObject);
px_void PX_Object_ScrollAreaMoveToTop(PX_Object *pObject);
px_void PX_Object_ScrollAreaGetRegion(PX_Object *pObject,px_float *left,px_float *top,px_float *right,px_float *bottom);
px_void PX_Object_ScrollAreaUpdateRange( PX_Object *pObject);
px_void PX_Object_ScrollAreaRender(px_surface *psurface, PX_Object *pObject,px_uint elpased);
px_void PX_Object_ScrollAreaSetBkColor(PX_Object *pObj,px_color bkColor);
px_void PX_Object_ScrollAreaSetBorder( PX_Object *pObj,px_bool Border );
px_void PX_Object_ScrollAreaSetBorderColor(PX_Object *pObj,px_color borderColor);
px_void PX_Object_ScrollAreaFree(PX_Object *pObj);


///////////////////////////////////////////////////////////////////////////////////////////////
//AutoText
typedef struct 
{
	px_color TextColor;
	PX_FontModule *fontModule;
	px_string text;
}PX_Object_AutoText;


PX_Object *PX_Object_AutoTextCreate(px_memorypool *mp,PX_Object *Parent,int x,int y,int limit_width,PX_FontModule *fm);
PX_Object_AutoText * PX_Object_GetAutoText( PX_Object *Object );
px_void PX_Object_AutoTextSetTextColor( PX_Object *pObject,px_color Color );
px_void PX_Object_AutoTextSetText(PX_Object *Obj,const px_char *Text);
px_void PX_Object_AutoTextRender(px_surface *psurface, PX_Object *pObject,px_uint elpased);
px_void PX_Object_AutoTextFree(PX_Object *Obj);
px_int PX_Object_AutoTextGetHeight(PX_Object *Obj);

//////////////////////////////////////////////////////////////////////////

PX_Object *PX_Object_AnimationCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,PX_Animationlibrary *lib);
px_void PX_Object_AnimationSetLibrary(PX_Object *Object,PX_Animationlibrary *lib);
PX_Object_Animation *PX_Object_GetAnimation(PX_Object *Object);
px_void	   PX_Object_AnimationSetAlign(PX_Object *pObject,px_dword Align);
px_void	   PX_Object_AnimationRender(px_surface *psurface,PX_Object *pImage,px_uint elpased);
px_void	   PX_Object_AnimationFree(PX_Object *pObject);


//////////////////////////////////////////////////////////////////////////
//CursorButton
//////////////////////////////////////////////////////////////////////////
typedef struct 
{
	PX_Object *pushbutton;
	px_float c_distance;
	px_float c_distance_far;
	px_float c_distance_near;
	px_color c_color;
	px_int c_width;
	px_bool enter;
}PX_Object_CursorButton;

//use pushbutton function to operate cursor-button
PX_Object *PX_Object_CursorButtonCreate(px_memorypool *mp,PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,const px_char *Text,PX_FontModule *fontmodule,px_color Color);
PX_Object_CursorButton * PX_Object_GetCursorButton( PX_Object *Object );
PX_Object * PX_Object_GetCursorButtonPushButton(PX_Object *Object);

//////////////////////////////////////////////////////////////////////////
//list
//////////////////////////////////////////////////////////////////////////

typedef px_bool (*PX_Object_ListItemOnCreate)(px_memorypool *mp,PX_Object *ItemObject);


typedef enum
{
	PX_LISTITEM_STATUS_NORMAL,
	PX_LISTITEM_STATUS_SELECTED,
}PX_LISTITEM_STATUS;

typedef struct
{
	PX_LISTITEM_STATUS status;
	px_void *pdata;
}PX_Object_ListItem;

typedef struct
{
	px_memorypool *mp;
	px_int ItemWidth;
	px_int ItemHeight;
	px_int offsetx;
	px_int offsety;
	px_int currentSelectedId;
	px_color BorderColor;
	px_color BackgroundColor;
	px_surface renderSurface;
	px_vector Items;
	px_vector pData;
	PX_Object *SliderBar;
	PX_Object_ListItemOnCreate CreateFunctions;
}PX_Object_List;

PX_Object_ListItem * PX_Object_GetListItem( PX_Object *Object );
PX_Object * PX_Object_ListCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,px_int ItemHeight,PX_Object_ListItemOnCreate _CreateFunc);
px_void PX_Object_ListClear(PX_Object *pListObj);
px_int PX_Object_ListAdd(PX_Object *pListObj,px_void *ptr);
px_void *PX_Object_ListGetItem(PX_Object *pListObject,px_int index);
px_void PX_Object_ListRemoveItem(PX_Object *pListObject,px_int index);
px_void PX_Object_ListSetBackgroundColor(PX_Object *pListObject,px_color color);
px_void PX_Object_ListSetBorderColor(PX_Object *pListObject,px_color color);


//////////////////////////////////////////////////////////////////////////
//
typedef struct
{
	px_int x,y,width,height;
	px_char u_key[8];
	px_char d_key[8];
	px_bool bCursor;
	px_bool bDown;
	px_bool bhold;
	
}PX_Object_VirtualKey;

typedef struct
{
	PX_Object_VirtualKey Keys[14+14+13+12+3];
	px_color backgroundColor;
	px_color borderColor;
	px_color cursorColor;
	px_color pushColor;
	px_char functionCode;
	PX_Object *LinkerObject;
	px_bool bTab,bUpper,bShift,bCtrl,bAlt;
}PX_Object_VirtualKeyBoard;

PX_Object* PX_Object_VirtualKeyBoardCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int width,px_int height);
px_void PX_Object_VirtualKeyBoardSetBackgroundColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualKeyBoardSetBorderColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualKeyBoardSetCursorColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualKeyBoardSetPushColor( PX_Object *pObject,px_color Color );
px_char PX_Object_VirtualKeyBoardGetCode(PX_Object *pObject);
px_void PX_Object_VirtualKeyBoardSetLinkerObject(PX_Object *pObject,PX_Object *linker);

typedef struct
{
	PX_Object_VirtualKey Keys[17];
	px_color backgroundColor;
	px_color borderColor;
	px_color cursorColor;
	px_color pushColor;
	px_char functionCode;
	PX_Object *LinkerObject;
}PX_Object_VirtualNumberKeyBoard;

PX_Object* PX_Object_VirtualNumberKeyBoardCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int width,px_int height);
px_void PX_Object_VirtualNumberKeyBoardSetBackgroundColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualNumberKeyBoardSetBorderColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualNumberKeyBoardSetCursorColor( PX_Object *pObject,px_color Color );
px_void PX_Object_VirtualNumberKeyBoardSetPushColor( PX_Object *pObject,px_color Color );
px_char PX_Object_VirtualNumberKeyBoardGetCode(PX_Object *pObject);
px_void PX_Object_VirtualNumberKeyBoardSetLinkerObject(PX_Object *pObject,PX_Object *linker);
//////////////////////////////////////////////////////////////////////////

#define  PX_OBJECT_COORDINATEDATA_MAP_LEFT  0
#define  PX_OBJECT_COORDINATEDATA_MAP_RIGHT 1
#define  PX_OBJECT_COORDINATEDATA_MAP_HORIZONTAL 2

#define  PX_OBJECT_COORDINATES_DEFAULE_MINHORIZONTALPIXELDIVIDING 48
#define  PX_OBJECT_COORDINATES_DEFAULE_MINVERTICALPIXELDIVIDING	  20
#define	 PX_OBJECT_COORDINATES_DEFAULE_DIVIDING					  10
#define  PX_OBJECT_COORDINATES_DEFAULT_SPACER					  64
#define  PX_OBJECT_COORDINATES_DEFAULT_VERTICALFLAG_OFFSET        8
#define  PX_OBJECT_COORDINATES_DEFAULT_FLAGTEXT_SPACER		      8

#define	 PX_OBJECT_COORDINATES_DEFAULT_FRAMELINE_WIDTH			  2
#define  PX_OBJECT_COORDINATES_DEFAULT_FONT_SIZE				  16
#define  PX_OBJECT_COORDINATES_DEFAULT_DASH_RGB					  255,100,100,255
#define  PX_OBJECT_COORDINATES_DEFAULT_LINE_WIDTH				  2.0f

#define  PX_OBJECT_COORDINATES_DEFAULT_EXPONENTIAL_FORMAT	     "%1.2e%2"
#define  PX_OBJECT_COORDINATES_DEFAULT_FLOAT_FLAGFORMAT_H		 "%1.2"
#define  PX_OBJECT_COORDINATES_DEFAULT_INT_FLAGFORMAT_H			 "%1"

#define  PX_OBJECT_COORDINATES_DEFAULT_FLOAT_FLAGFORMAT_L		 "%1.2"
#define  PX_OBJECT_COORDINATES_DEFAULT_INT_FLAGFORMAT_L			 "%1"

#define  PX_OBJECT_COORDINATES_DEFAULT_FLOAT_FLAGFORMAT_R		 "%1.2"
#define  PX_OBJECT_COORDINATES_DEFAULT_INT_FLAGFORMAT_R			 "%1"


#define  PX_OBJECT_COORDINATEFLAGLINE_XSHOW						 1
#define  PX_OBJECT_COORDINATEFLAGLINE_YLSHOW					 2
#define  PX_OBJECT_COORDINATEFLAGLINE_YRSHOW					 4

typedef enum 
{
	PX_OBJECT_COORDINATES_LINEMODE_LINES=0,
	PX_OBJECT_COORDINATES_LINEMODE_PILLAR=1,
}PX_OBJECT_COORDINATES_LINEMODE;

typedef enum 
{
	PX_OBJECT_COORDINATES_GUIDESSHOWMODE_ALL=0,
	PX_OBJECT_COORDINATES_GUIDESSHOWMODE_HORIZONTAL=1,
	PX_OBJECT_COORDINATES_GUIDESSHOWMODE_VERTICAL=2
}PX_OBJECT_COORDINATES_GUIDESSHOWMODE;

typedef enum
{
	PX_OBJECT_COORDINATES_COORDINATEDATA_MAP_LEFT,
	PX_OBJECT_COORDINATES_COORDINATEDATA_MAP_RIGHT,
}PX_OBJECT_COORDINATES_COORDINATEDATA_MAP;

typedef enum
{
	PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE_NORMAL,
	PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE_EXPONENTRAL,
}PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE;


typedef struct  
{
	px_double	X,Y;
	px_color	color;
	px_float	LineWidth;
	px_uchar    XYshow;
}PX_Object_CoordinateFlagLine;

typedef struct 
{
	px_double *MapHorizontalArray;
	px_double *MapVerticalArray;
	px_double Normalization;
	px_color  Color;
	PX_OBJECT_COORDINATES_COORDINATEDATA_MAP Map;
	px_int	  linewidth;
	px_int    ID;
	px_int	  Visibled;
	px_int	  Size;
}PX_Object_CoordinateData;


typedef struct
{
	px_memorypool *mp;
	px_double HorizontalRangeMin;
	px_double HorizontalRangeMax;
	px_double LeftVerticalRangeMin,LeftVerticalRangeMax;
	px_double RightVerticalRangeMin,RightVerticalRangeMax;
	PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE leftTextDisplayMode,RightTextDisplayMode;

	px_double ResHorizontalRangeMin;
	px_double ResHorizontalRangeMax;
	px_double ResLeftVerticalRangeMin,ResLeftVerticalRangeMax;
	px_double ResRightVerticalRangeMin,ResRightVerticalRangeMax;


	px_int MinVerticalPixelDividing;
	px_int MinHorizontalPixelDividing;
	px_int HorizontalDividing;
	px_int LeftVerticalDividing;
	px_int RightVerticalDividing;

	px_int LeftSpacer,RightSpacer,TopSpacer,BottomSpacer;

	const px_char *Exponential_Format;
	const px_char *FloatFlagFormat_H;
	const px_char *IntFlagFormat_H;
	const px_char *FloatFlagFormat_L;
	const px_char *IntFlagFormat_L;
	const px_char *FloatFlagFormat_R;
	const px_char *IntFlagFormat_R;
	const px_char *LeftTitle,*RightTitle,*TopTitle,*BottomTitle;

	px_point DragStartPoint;
	px_point DragingPoint;
	px_int bScaleDrag;
	px_int bScaling;
	px_int MarkLineX;

	px_bool ScaleEnabled;
	px_bool ShowGuides;
	px_bool MarkValueEnabled;
	px_bool OnMarkStatus;
	px_bool bDataUpdatePainter;
	px_bool ShowHelpLine;

	px_bool LeftTextShow,RightTextShow,HorizontalTextShow;

	px_color DashColor;
	px_color FontColor;
	px_color borderColor;
	px_color helpLineColor;
	int      FontSize;

	PX_OBJECT_COORDINATES_LINEMODE LineMode;
	PX_OBJECT_COORDINATES_GUIDESSHOWMODE guidesShowMode;

	px_float DataLineWidth;
	px_float DataPillarWidth;

	px_float GuidesLineWidth;
	px_vector  vData;
	px_vector  vFlagLine;

	px_int  helpLineX,helpLineY;
	PX_FontModule *fontmodule;
}PX_Object_Coordinates;


PX_Object_Coordinates *PX_Object_GetCoordinates(PX_Object *pObject);
// 
px_void PX_Object_CoordinatesSetMinVerticalPixelDividing(PX_Object *pObject,int val);
px_void PX_Object_CoordinatesSetMinHorizontalPixelDividing(PX_Object *pObject,int val);
px_void PX_Object_CoordinatesSetHorizontalDividing(PX_Object *pObject,int Count);
px_void PX_Object_CoordinatesSetLeftVerticalDividing(PX_Object *pObject,int Count);
px_void PX_Object_CoordinatesSetRightVerticalDividing(PX_Object *pObject,int Count);
px_void PX_Object_CoordinatesSetStyle(PX_Object *pObject,PX_OBJECT_COORDINATES_LINEMODE mode);
px_void PX_Object_CoordinatesSetScaleEnabled(PX_Object *pObject,px_bool Enabled);
px_void PX_Object_CoordinatesSetGuidesVisible(PX_Object *pObject,px_bool Visible); 
px_void PX_Object_CoordinatesSetGuidesShowMode(PX_Object *pObject,PX_OBJECT_COORDINATES_GUIDESSHOWMODE mode);
px_void PX_Object_CoordinatesShowHelpLine(PX_Object *pObject,px_bool show); 

px_void PX_Object_CoordinatesSetDataLineWidth(PX_Object *pObject,px_float linewidth );
px_void PX_Object_CoordinatesSetDataShow(PX_Object *pObject,px_int index,px_bool show );
px_void PX_Object_CoordinatesSetGuidesLineWidth(PX_Object *pObject,px_float linewidth);
px_void PX_Object_CoordinatesSetGuidesLineColor(PX_Object *pObject,px_color clr);
px_void PX_Object_CoordinatesSetTitleFontSize(PX_Object *pObject,int size);
px_void PX_Object_CoordinatesSetTitleFontColor(PX_Object *pObject,px_color clr);
px_void PX_Object_CoordinatesSetDashLineColor(PX_Object *pObject,px_color clr);
px_void PX_Object_CoordinatesSetLeftTextShow(PX_Object *pObject,px_bool bshow);
px_void PX_Object_CoordinatesSetRightTextShow(PX_Object *pObject,px_bool bshow);
px_void PX_Object_CoordinatesSetHorizontalTextShow(PX_Object *pObject,px_bool bshow);
px_void PX_Object_CoordinatesSetFloatFlagFormatHorizontal(PX_Object *pObject,const char *fmt);
px_void PX_Object_CoordinatesSetIntFlagFormatHorizontal(PX_Object *pObject,const char *fmt);
px_void PX_Object_CoordinatesSetFloatFlagFormatVerticalLeft(PX_Object *pObject,const char *fmt);
px_void PX_Object_CoordinatesSetIntFlagFormatVerticalLeft(PX_Object *pObject,const char *fmt);
px_void PX_Object_CoordinatesSetFloatFlagFormatVerticalRight(PX_Object *pObject,const char *fmt);
px_void PX_Object_CoordinatesSetIntFlagFormatVericalRight(PX_Object *pObject,const char *fmt);


px_void PX_Object_CoordinatesSetLeftTextMode(PX_Object *pObject,PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE mode);
px_void PX_Object_CoordinatesSetRightTextMode(PX_Object *pObject,PX_OBJECT_COORDINATES_TEXT_DISPLAYMODE mode);
px_void PX_Object_CoordinatesSetHorizontalMin(PX_Object *pObject,double Min);
px_void PX_Object_CoordinatesSetHorizontalMax(PX_Object *pObject,double Max);
px_void PX_Object_CoordinatesSetLeftVerticalMin(PX_Object *pObject,double Min);
px_void PX_Object_CoordinatesSetLeftVerticalMax(PX_Object *pObject,double Max);
px_void PX_Object_CoordinatesSetRightVerticalMax(PX_Object *pObject,double Max);
px_void PX_Object_CoordinatesSetRightVerticalMin(PX_Object *pObject,double Min);

px_void PX_Object_CoordinatesSetBorderColor(PX_Object *pObject,px_color clr);
PX_Object_CoordinateData *PX_Object_CoordinatesGetCoordinateData(PX_Object *pObject,px_int index);
int PX_Object_CoordinatesGetCoordinateWidth(PX_Object *pObject);
int PX_Object_CoordinatesGetCoordinateHeight(PX_Object *pObject);
//px_void PX_Object_CoordinatesSetTitleLeft(PX_Object *pObject,const px_char * title);
//px_void PX_Object_CoordinatesSetTitleRight(PX_Object *pObject,const px_char * title);
px_void PX_Object_CoordinatesSetTitleTop(PX_Object *pObject,const px_char * title);
px_void PX_Object_CoordinatesSetTitleBottom(PX_Object *pObject,const px_char * title);


px_void PX_Object_CoordinatesSetMarkValueEnabled(PX_Object *pObject,px_bool Enabled);
px_void PX_Object_CoordinatesSetFontColor(PX_Object *pObject,px_color clr);
px_void PX_Object_CoordinatesClearContext(PX_Object *pObject);
px_void PX_Object_CoordinatesClearFlagLine(PX_Object *pObject);
px_void PX_Object_CoordinatesAddData(PX_Object *pObject,PX_Object_CoordinateData data);
px_void PX_Object_CoordinatesAddCoordinateFlagLine(PX_Object *pObject,PX_Object_CoordinateFlagLine Line);
// 
px_void PX_Object_CoordinatesSetMargin(PX_Object *pObject,px_int Left,px_int Right,px_int Top,px_int Bottom);
px_void PX_Object_CoordinatesRestoreCoordinates(PX_Object *pObject);
PX_Object *PX_Object_CoordinatesCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,PX_FontModule *fontmodule);


#define PX_OBJECT_FILTER_EDITOR_MAX_PT 256
#define PX_OBJECT_FILTER_EDITOR_DEFAULT_RADIUS 6

typedef enum
{
	PX_OBJECT_FILTER_TYPE_Liner,
	PX_OBJECT_FILTER_TYPE_dB,
}PX_OBJECT_FILTER_TYPE;


typedef struct
{
	px_int x,y;
	px_bool bselect;
	px_bool bCursor;
}PX_Object_FilterEditor_OperatorPoint;


typedef struct
{
	px_bool ShowHelpLine;
	px_color FontColor;
	px_color borderColor;
	px_color helpLineColor;
	px_color ptColor;
	px_bool showHorizontal;
	int      FontSize;
	px_int   HorizontalDividing;
	px_int   VerticalDividing;
	px_point DragStartPoint;
	px_point lastAdjustPoint;
	px_point DragingPoint;
	px_int	 bSelectDrag;
	px_int	 bAdjust;
	px_int   opCount;
	px_int   radius;
	px_double rangedb;
	PX_OBJECT_FILTER_TYPE FilterType;
	PX_Object_FilterEditor_OperatorPoint pt[PX_OBJECT_FILTER_EDITOR_MAX_PT];
}PX_Object_FilterEditor;

PX_Object_FilterEditor *PX_Object_GetFilterEditor(PX_Object *Object);

PX_Object *PX_Object_FilterEditorCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,PX_OBJECT_FILTER_TYPE type);
px_void PX_Object_FilterEditorSethelpLineColor(PX_Object *Object,px_color clr);
px_void PX_Object_FilterEditorSetptColor(PX_Object *Object,px_color clr);

px_void PX_Object_FilterEditorSetOperateCount(PX_Object *Object,px_int opcount);
px_void PX_Object_FilterEditorSetType(PX_Object *Object,PX_OBJECT_FILTER_TYPE type);
px_void PX_Object_FilterEditorSetHorizontalShow(PX_Object *Object,px_bool HorizontalShow);
px_void PX_Object_FilterEditorReset(PX_Object *Object);
px_void PX_Object_FilterEditorSetRange(PX_Object *Object,px_double range);
px_void PX_Object_FilterEditorSetFontColor(PX_Object *Object,px_color clr);
px_void PX_Object_FilterEditorSetBorderColor(PX_Object *Object,px_color clr);
px_void PX_Object_FilterEditorSethelpLineColor(PX_Object *Object,px_color clr);
px_void PX_Object_FilterEditorSetFontSize(PX_Object *Object,px_int size);
px_void PX_Object_FilterEditorSetHorizontalDividing(PX_Object *Object,px_int div);
px_void PX_Object_FilterEditorSetVerticalDividing(PX_Object *Object,px_int div);
px_void PX_Object_FilterEditorMapData(PX_Object *Object,px_double data[],px_int size);
px_double PX_Object_FilterEditorMapValue(PX_Object *Object,px_double precent);


#define PX_OBJECT_CHECKBOX_MAX_CONTENT 64


typedef enum
{
	PX_OBJECT_CHECKBOX_STATE_ONCURSOR,
	PX_OBJECT_CHECKBOX_STATE_ONPUSH,
	PX_OBJECT_CHECKBOX_STATE_NORMAL,
}PX_Object_CHECKBOX_STATE;

typedef struct  
{
	px_dword Align;
	px_bool Border;
	px_color TextColor;
	px_color BorderColor;
	px_color BackgroundColor;
	px_color CursorColor;
	px_color PushColor;
	px_char Text[PX_OBJECT_CHECKBOX_MAX_CONTENT];
	px_bool bCheck;
	PX_FontModule *fm;
	PX_Object_CHECKBOX_STATE state;
}PX_Object_CheckBox;

PX_Object_CheckBox *PX_Object_GetCheckBox(PX_Object *Object);
PX_Object * PX_Object_CheckBoxCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,const char text[],PX_FontModule *fm);
px_bool PX_Object_CheckBoxGetCheck(PX_Object *Object);
px_void PX_Object_CheckBoxSetBackgroundColor(PX_Object *Object,px_color clr);
px_void PX_Object_CheckBoxSetBorderColor(PX_Object *Object,px_color clr);
px_void PX_Object_CheckBoxSetPushColor(PX_Object *Object,px_color clr);
px_void PX_Object_CheckBoxSetCursorColor(PX_Object *Object,px_color clr);
px_void PX_Object_CheckBoxSetText(PX_Object *Object,const px_char text[]);
px_void PX_Object_CheckBoxSetTextColor(PX_Object *Object,px_color clr);
px_void PX_Object_CheckBoxSetCheck(PX_Object *Object,px_bool check);




#define PX_MENU_CONTENT_MAX_LEN 48
#define PX_MENU_ITEM_SPACER_SIZE 2
typedef px_void (*PX_MenuExecuteFunc)(px_void *userPtr);


struct _PX_Object_Menu_Item
{
	struct _PX_Object_Menu_Item *pParent;
	px_int  x,y,width,height;
	px_char Text[PX_MENU_CONTENT_MAX_LEN];
	px_bool onCursor;
	px_bool Activated;
	px_list Items;
	PX_MenuExecuteFunc func_callback;
	px_void *user_ptr;
};
typedef struct _PX_Object_Menu_Item PX_Object_Menu_Item;

typedef struct
{
	px_memorypool *mp;
	px_bool activating;
	px_int minimumSize;
	PX_Object_Menu_Item root;
	PX_FontModule *fontmodule;
	px_color backgroundColor;
	px_color fontColor;
	px_color cursorColor;
}PX_Object_Menu;


PX_Object * PX_Object_MenuCreate(px_memorypool *mp,PX_Object *Parent,px_int x,int y,px_int width,PX_FontModule *fontmodule);
PX_Object_Menu_Item * PX_Object_MenuGetRootItem(PX_Object *pMenuObject);
PX_Object_Menu_Item * PX_Object_MenuAddItem(PX_Object *pMenuObject,PX_Object_Menu_Item *parent,const px_char Text[],PX_MenuExecuteFunc _callback,px_void *ptr);


typedef enum
{
	PX_OBJECT_SELECTBAR_STYLE_RECT,
	PX_OBJECT_SELECTBAR_STYLE_ROUNDRECT,
}PX_OBJECT_SELECTBAR_STYLE;


typedef struct
{
	px_char Text[PX_MENU_CONTENT_MAX_LEN];
	px_bool onCursor;
}PX_Object_SelectBar_Item;;

typedef struct
{
	px_memorypool *mp;
	px_int	maxDisplayCount;
	px_int  currentDisplayOffsetIndex;
	px_int  ItemHeight;
	px_bool activating;
	px_bool onCursor;
	px_vector Items;//PX_Object_SelectBar_Item;
	PX_FontModule *fontmodule;
	px_color backgroundColor;
	px_color fontColor;
	px_color cursorColor;
	px_color borderColor;
	px_int   selectIndex;
	PX_Object *sliderBar;
	PX_OBJECT_SELECTBAR_STYLE style;
}PX_Object_SelectBar;

PX_Object_SelectBar *PX_Object_GetSelectBar(PX_Object *pSelecrBar);
PX_Object * PX_Object_SelectBarCreate(px_memorypool *mp,PX_Object *Parent,px_int x,int y,px_int width,px_int height,PX_FontModule *fontmodule);
px_int  PX_Object_SelectBarAddItem(PX_Object *PX_Object_SelectBar,const px_char Text[]);
px_void PX_Object_SelectBarRemoveItem(PX_Object *PX_Object_SelectBar,px_int index);
px_int PX_Object_SelectBarGetItemIndexByText(PX_Object *pObject,const px_char Text[]);
const px_char *PX_Object_SelectBarGetCurrentText(PX_Object *pObject);
px_void PX_Object_SelectBarSetDisplayCount(PX_Object *pObject,px_int count);
px_int  PX_Object_SelectBarGetCurrentIndex(PX_Object *pObject);
px_void  PX_Object_SelectBarSetCurrentIndex(PX_Object *pObject,px_int index);
px_void PX_Object_SelectBarSetStyle(PX_Object *pObject,PX_OBJECT_SELECTBAR_STYLE style);
px_void PX_Object_SelectBarSetFontColor(PX_Object *pObject,px_color color);
px_void PX_Object_SelectBarSetCursorColor(PX_Object *pObject,px_color color);
px_void PX_Object_SelectBarSetBorderColor(PX_Object *pObject,px_color color);
px_void PX_Object_SelectBarSetBackgroundColor(PX_Object *pObject,px_color color);


typedef enum
{
	PX_OBJECT_RADIOBOX_STATE_ONCURSOR,
	PX_OBJECT_RADIOBOX_STATE_ONPUSH,
	PX_OBJECT_RADIOBOX_STATE_NORMAL,
}PX_Object_RADIOBOX_STATE;

typedef struct  
{
	PX_ALIGN Align;
	px_bool Border;
	px_color TextColor;
	px_color BorderColor;
	px_color BackgroundColor;
	px_color CursorColor;
	px_color PushColor;
	px_char Text[PX_OBJECT_CHECKBOX_MAX_CONTENT];
	px_bool bCheck;
	PX_FontModule *fm;
	PX_Object_RADIOBOX_STATE state;
}PX_Object_RadioBox;

PX_Object_RadioBox *PX_Object_GetRadioBox(PX_Object *Object);
PX_Object * PX_Object_RadioBoxCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,const char text[],PX_FontModule *fm);
px_bool PX_Object_RadioBoxGetCheck(PX_Object *Object);
px_void PX_Object_RadioBoxSetBackgroundColor(PX_Object *Object,px_color clr);
px_void PX_Object_RadioBoxSetBorderColor(PX_Object *Object,px_color clr);
px_void PX_Object_RadioBoxSetPushColor(PX_Object *Object,px_color clr);
px_void PX_Object_RadioBoxSetCursorColor(PX_Object *Object,px_color clr);
px_void PX_Object_RadioBoxSetText(PX_Object *Object,const px_char text[]);
px_void PX_Object_RadioBoxSetTextColor(PX_Object *Object,px_color clr);
px_void PX_Object_RadioBoxSetCheck(PX_Object *Object,px_bool check);

//////////////////////////////////////////////////////////////////////////
//explorer
#define PX_EXPLORER_MAX_PATH_LEN 260
#define PX_EXPLORER_MAX_ITEMS  1024
#define PX_OBJECT_EXPOLRER_MENU_HEIGHT 48
#define PX_OBJECT_EXPOLRER_ITEM_HEIGHT 38
#define PX_OBJECT_EXPOLRER_SLIDERBAR_WIDTH 24
#define PX_OBJECT_EXPOLRER_BUTTON_WIDTH 64
typedef px_int (*PX_ExplorerGetPathFolderCount)(const px_char *path,const char *filter);
typedef px_int (*PX_ExplorerGetPathFileCount)(const px_char *path,const char *filter);
typedef px_int (*PX_ExplorerGetPathFolderName)(const char path[],int count,char FileName[][260],const char *filter);
typedef px_int (*PX_ExplorerGetPathFileName)(const char path[],int count,char FileName[][260],const char *filter);

typedef struct  
{
	px_bool bFolder;
	px_bool bcursor;
	px_bool bselect;
	px_char name[260];
}PX_Object_Explorer_Item;

typedef enum
{
	PX_OBJECT_EXPLORER_RETURN_CONFIRM,
	PX_OBJECT_EXPLORER_RETURN_CANCEL,
}PX_OBJECT_EXPLORER_RETURN;


typedef struct  
{
	PX_ExplorerGetPathFolderCount func_getpathfoldercount;
	PX_ExplorerGetPathFileCount func_getpathfilecount;
	PX_ExplorerGetPathFolderName func_getpathfoldername;
	PX_ExplorerGetPathFileName func_getpathfilename;
	px_int ItemCount;
	px_int MaxSelectedCount;
	PX_FontModule *fontmodule;
	PX_Object_Explorer_Item Items[PX_EXPLORER_MAX_ITEMS];

	PX_Object *edit_Path;
	PX_Object *btn_Back,*btn_go,*btn_Ok,*btn_Cancel;
	PX_Object *SliderBar;
	const px_char *filter;

	px_shape file,folder;

	px_color backgroundcolor,cursorcolor,fontcolor,bordercolor,pushcolor;

	PX_OBJECT_EXPLORER_RETURN returnType;

}PX_Object_Explorer;

PX_Object_Explorer *PX_Object_GetExplorer(PX_Object *Object);
PX_Object * PX_Object_ExplorerCreate(px_memorypool *mp, PX_Object *Parent,px_int x,px_int y,px_int Width,px_int Height,PX_FontModule *fm,
	PX_ExplorerGetPathFolderCount _func_gpfdc,
	PX_ExplorerGetPathFileCount _func_gpfec,
	PX_ExplorerGetPathFolderName _func_gpfdn,
	PX_ExplorerGetPathFileName _func_gpfcn,
	const px_char path[260]
	);
px_void PX_Object_ExplorerSetBorderColor(PX_Object *Object,px_color clr);
px_void PX_Object_ExplorerSetPushColor(PX_Object *Object,px_color clr);
px_void PX_Object_ExplorerSetCursorColor(PX_Object *Object,px_color clr);
px_void PX_Object_ExplorerSetTextColor(PX_Object *Object,px_color clr);
px_void PX_Object_ExplorerSetCheck(PX_Object *Object,px_bool check);
px_void PX_Object_ExplorerRefresh(PX_Object *Object);
px_int PX_Object_ExplorerGetSelectedCount(PX_Object *Object);
px_void PX_Object_ExplorerGetPath(PX_Object *Object,px_char path[PX_EXPLORER_MAX_PATH_LEN],px_int index);
px_void PX_Object_ExplorerOpen(PX_Object *Object);
px_void PX_Object_ExplorerClose(PX_Object *Object);
#endif