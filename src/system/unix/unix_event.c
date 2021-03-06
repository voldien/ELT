#include"system/elt_event.h"
#include"system/unix/unix_win.h"

#include<X11/X.h>
#include<X11/Xlib.h>

static inline void private_ExDecodeEvent(ExEvent* event, XEvent msg) {
	event->event = 0;

	/**
	 *
	 *
	 */
	switch (msg.type) {

	case KeyPress: {
		event->event |= EX_EVENT_KEY;
		event->event |= EX_EVENT_KEY_PRESSED;
		event->key.code = XLookupKeysym(&msg.xkey, 0);
		event->mouse.x = msg.xkey.x;
		event->mouse.y = msg.xkey.y;
		event->key.alt = msg.xkey.state & Mod1Mask;
		event->key.ctrl = msg.xkey.state & ControlMask;
		event->key.shift = msg.xkey.state & ShiftMask;
		event->key.system = msg.xkey.state & Mod1Mask;

	}
		break;
	case KeyRelease: {
		event->event |= EX_EVENT_KEY;
		event->event |= EX_EVENT_KEY_RELEASE;
		event->key.code = XLookupKeysym(&msg.xkey, 0);
		event->mouse.x = msg.xkey.x;
		event->mouse.y = msg.xkey.y;
		event->key.alt = msg.xkey.state & Mod1Mask;
		event->key.ctrl = msg.xkey.state & ControlMask;
		event->key.shift = msg.xkey.state & ShiftMask;
		event->key.system = msg.xkey.state & Mod1Mask;

	}
		break;
	case ButtonPress: {
		event->event |= EX_EVENT_MOUSE;
		event->event |= EX_EVENT_MOUSE_PRESSED;
		event->button.button = msg.xbutton.button;
		event->mouse.x = msg.xkey.x;
		event->mouse.y = msg.xkey.y;
	}
		break;

	case ButtonRelease: {
		event->event |= EX_EVENT_MOUSE;
		event->event |= EX_EVENT_MOUSE_RELEASED;
		event->button.button = msg.xbutton.button;
		event->mouse.x = msg.xkey.x;
		event->mouse.y = msg.xkey.y;

	}
		break;
	case MotionNotify: {
		event->event |= EX_EVENT_MOUSE_MOTION;
		event->motion.xdelta = msg.xmotion.x - msg.xkey.x;
		event->motion.ydelta = msg.xmotion.y - msg.xkey.y;
		event->motion.x = msg.xmotion.x;
		event->motion.y = msg.xmotion.y;
	}
		break;
	case LeaveNotify:
		event->event |= EX_EVENT_ON_UNFOCUSE;
		break;
	case EnterNotify:
		event->event |= EX_EVENT_ON_FOCUSE;
		break;
	case GravityNotify:
		event->event |= EX_EVENT_WINDOW_MOVE;
		break;
	case ResizeRequest: {
		event->event |= EX_EVENT_SIZE;
		event->size.width = msg.xresizerequest.width;
		event->size.height = msg.xresizerequest.height;
	}
		break;
	case Expose: {
		event->event |= EX_EVENT_EXPOSE;
		event->size.width = msg.xexpose.width;
		event->size.height = msg.xexpose.height;
	}
		break;
	case ClientMessage: {
		//event->event |= EX_EVENT_SIZE;
		/*
		 if((Atom)msg.xclient.data.l[0] == wm_delete_window){

		 }
		 */

	}
		break;
	case VisibilityNotify: {
		/*
		 if(msg.xvisibility.state == VisibilityUnobscured)
		 event->event |= EX_EVENT_WINDOW_SHOW;
		 else if(msg.xvisibility.state == VisibilityPartiallyObscured || msg.xvisibility.state == VisibilityFullyObscured)
		 event->event |= EX_EVENT_WINDOW_HIDE;
		 */
	}
		break;
	case ConfigureNotify: {
		XConfigureEvent xce = msg.xconfigure;
		event->event |= EX_EVENT_SIZE;
		event->size.width = msg.xconfigure.width;
		event->size.height = msg.xconfigure.height;
	}
		break;
	case DestroyNotify: {
		event->event |= EX_EVENT_WINDOW_DESTROYED;
		event->destroy.window = msg.xdestroywindow.event;

	}
		break;
	case FocusIn:
		event->event |= EX_EVENT_ON_FOCUSE;
		break;
	case FocusOut:
		event->event |= EX_EVENT_ON_UNFOCUSE;
		break;
	case KeymapNotify:
		XRefreshKeyboardMapping(&msg.xmapping);
		break;
	case ReparentNotify:
		event->event |= EX_EVENT_WINDOW_REPARENT;
		break;
	case PropertyNotify:
		break;
	case MapNotify:
		event->event |= EX_EVENT_WINDOW_SHOW;
		break;
	case UnmapNotify:
		event->event |= EX_EVENT_WINDOW_HIDE;
		break;
	case LASTEvent:
		event->event = 0;
		//return EX_FALSE;
		break;
	default:
		event->event |= msg.type;
		break;
	}

	event->time = ExGetTicks(); /*	TODO check if to use ExGetHiRes() instead.	*/
	event->window = msg.xany.window; /*	*/
}

int ExPollEvent(ExEvent* event) {

	XEvent msg;
	if (XPending(display)) {
		XNextEvent(display, &msg);
		private_ExDecodeEvent(event, msg);

		return EX_TRUE;
	} else {/*XSync(display,EX_TRUE);*/
		return EX_FALSE;
	}
}

int ExPollWindowEvent(ExWin window, ExWindowEvent* event) {
	XEvent msg;
	if (XPending(display)) {
		XWindowEvent(display, window, 0, &msg);
		private_ExDecodeEvent(event, msg);
	} else {
		/*XSync(display,EX_TRUE);*/return EX_FALSE;
	}
	return EX_TRUE;
}

int ExForwardEvent(unsigned int event, ExHandle data, unsigned int size) {
	return XSendEvent(display, 0, True, event, data);
}
