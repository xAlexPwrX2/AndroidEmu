//============================================================================
//
//   SSSS    tt          lll  lll       
//  SS  SS   tt           ll   ll        
//  SS     tttttt  eeee   ll   ll   aaaa 
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2010 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: GuiObject.hxx 2001 2010-04-10 21:37:23Z stephena $
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef GUI_OBJECT_HXX
#define GUI_OBJECT_HXX

class Dialog;
class DialogContainer;
class Widget;

#include "Command.hxx"
#include "OSystem.hxx"
#include "Array.hxx"

typedef Common::Array<Widget*> WidgetArray;

// The commands generated by various widgets
enum {
  kOKCmd           = 'OK  ',
  kCloseCmd        = 'CLOS',
  kNextCmd         = 'NEXT',
  kPrevCmd         = 'PREV',
  kEditCmd         = 'EDIT',
  kDefaultsCmd     = 'DEFA',
  kSetPositionCmd  = 'SETP',
  kTabChangedCmd   = 'TBCH',
  kCheckActionCmd  = 'CBAC',
  kRefreshAllCmd   = 'REFA'
};

/**
  This is the base class for all GUI objects/widgets.
  
  @author  Stephen Anthony
  @version $Id: GuiObject.hxx 2001 2010-04-10 21:37:23Z stephena $
*/
class GuiObject : public CommandReceiver
{
  friend class Widget;
  friend class DialogContainer;

  public:
    GuiObject(OSystem& osystem, DialogContainer& parent, Dialog& dialog,
              int x, int y, int w, int h)
      : myOSystem(osystem),
        myParent(parent),
        myDialog(dialog),
        _x(x),
        _y(y),
        _w(w),
        _h(h),
        _dirty(false),
        _firstWidget(0) {}

    virtual ~GuiObject() {}

    OSystem& instance()       { return myOSystem; }
    DialogContainer& parent() { return myParent;  }
    Dialog& dialog()          { return myDialog;  }

    virtual int getAbsX() const     { return _x; }
    virtual int getAbsY() const     { return _y; }
    virtual int getChildX() const   { return getAbsX(); }
    virtual int getChildY() const   { return getAbsY(); }
    virtual int getWidth() const    { return _w; }
    virtual int getHeight() const   { return _h; }

    virtual void setWidth(int w)    { _w = w; }
    virtual void setHeight(int h)   { _h = h; }

    virtual void setDirty() { _dirty = true; }

    virtual bool isVisible() const = 0;
    virtual void draw() = 0;

    /** Add given widget to the focus list */
    virtual void addFocusWidget(Widget* w) = 0;

    /** Return focus list for this object */
    WidgetArray& getFocusList() { return _focusList; }

    /** Redraw the focus list */
    virtual void redrawFocus() {}

  protected:
    virtual void releaseFocus() = 0;

  private:
    OSystem&         myOSystem;
    DialogContainer& myParent;
    Dialog&          myDialog;

  protected:
    int _x, _y;
    int _w, _h;
    bool _dirty;

    Widget* _firstWidget;
    WidgetArray _focusList;
};

#endif
