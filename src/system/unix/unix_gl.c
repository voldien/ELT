#include"system/elt_gl.h"
#include"elt_loadso.h"
#include"elt_timer.h"

#include"system/unix/unix_win.h"

#include<X11/extensions/Xrender.h>

#include<X11/Xatom.h>
#include<X11/keysym.h>
#include<EGL/egl.h>
#include<EGL/eglext.h>

#include<GL/glx.h>

#if defined(GL_ES_VERSION_3_0)  && !defined(__gl_h_)
#include<GLES3/gl3.h>
#include<GLES3/gl3ext.h>
#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)  && !defined(__gl_h_)
#include<GLES2/gl2.h>
#include<GLES2/gl2ext.h>
#include<GLES2/gl2platform.h>
#else
#include<GL/glx.h>
#include<GL/glxext.h>
#include<GL/glu.h>
#endif

#define GL_GET_PROC(x) glXGetProcAddress((const char*)( x ) )           /*  get OpenGL function process address */

#define PIXATTOFFSET 8	/*	offset to variable	*/
#define PIXCONTEXTOFFSET 22

int pixAtt[] = {
GLX_RENDER_TYPE, GLX_RGBA_BIT,
GLX_X_RENDERABLE, True,
GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,

/*		*/
GLX_RED_SIZE, 8,
GLX_GREEN_SIZE, 8,
GLX_BLUE_SIZE, 8,
GLX_DEPTH_SIZE, 24,
GLX_ALPHA_SIZE, 0,
GLX_DOUBLEBUFFER, True,
GLX_STENCIL_SIZE, 0,
GLX_ACCUM_RED_SIZE, 0,
GLX_ACCUM_GREEN_SIZE, 0,
GLX_ACCUM_BLUE_SIZE, 0,
GLX_ACCUM_ALPHA_SIZE, 0,
GLX_VISUAL_ID, 0,

/*	GLX	*/
GLX_STEREO, 0,
GLX_SAMPLE_BUFFERS_ARB, 0,
GLX_SAMPLES_ARB, 0,
GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB, False,
None, None,

GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
GLX_CONTEXT_MINOR_VERSION_ARB, 0,
#ifdef EX_DEBUG
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB, /*  Debug TODO add hint*/
#else
		GLX_CONTEXT_FLAGS_ARB, 0,
#endif

		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		None, None, };

static void ExDescribeFBbconfig(GLXFBConfig* fbconfig) {
#ifdef EX_DEBUG
	int doublebuffer;
	int red_bits, green_bits, blue_bits, alpha_bits, depth_bits;

	glXGetFBConfigAttrib(display, *fbconfig, GLX_DOUBLEBUFFER, &doublebuffer);
	glXGetFBConfigAttrib(display, *fbconfig, GLX_RED_SIZE, &red_bits);
	glXGetFBConfigAttrib(display, *fbconfig, GLX_GREEN_SIZE, &blue_bits);
	glXGetFBConfigAttrib(display, *fbconfig, GLX_BLUE_SIZE, &green_bits);
	glXGetFBConfigAttrib(display, *fbconfig, GLX_ALPHA_SIZE, &alpha_bits);
	glXGetFBConfigAttrib(display, *fbconfig, GLX_DEPTH_SIZE, &depth_bits);

	fprintf(stdout,
			"FBConfig selected:\n"
					"Doublebuffer: %s\n"
					"Red Bits: %d, Green Bits: %d, Blue Bits: %d, Alpha Bits: %d, Depth Bits: %d\n",
			doublebuffer == True ? "Yes" : "No", red_bits, green_bits,
			blue_bits, alpha_bits, depth_bits);
#endif
}

int ExChooseFBconfig(GLXFBConfig* pfbconfig) {
	GLXFBConfig* fbconfigs;
	XVisualInfo* visual;
	XRenderPictFormat *pict_format;
	int numfbconfigs, i;
	unsigned int attr;
	ExBoolean isFBConfigSet = EX_FALSE;

	fbconfigs = glXChooseFBConfig(display, DefaultScreen(display), pixAtt,
			&numfbconfigs);
	if (fbconfigs == NULL) {
		/*	Invalid attributes.	*/
		fbconfigs = glXGetFBConfigs(display, DefaultScreen(display),
				&numfbconfigs);

	}

	for (i = 0; i < numfbconfigs; i++) {
		visual = (XVisualInfo*) glXGetVisualFromFBConfig(display, fbconfigs[i]);
		if (!visual) {
			continue;
		}

		pict_format = XRenderFindVisualFormat(display, visual->visual);
		if (!pict_format) {
			goto end;
		}

		pfbconfig[0] = fbconfigs[i];
		if (ExOpenGLGetAttribute(EX_OPENGL_ALPHA_SIZE, &attr) > 0) {
			if (pict_format->direct.alphaMask > 0) {
				XFree(visual);
				break;
			}

		} else {
			XFree(visual);
			break;
		}

		end:

		XFree(visual); /*TODO fix loop such that is gets properly free.*/
	}
	ExDescribeFBbconfig(pfbconfig);

	/* Be sure to free the FBConfig list allocated by glXChooseFBConfig()	*/
	XFree(fbconfigs);

	return 1;
}

ExOpenGLContext ExCreateTempGLContext(void) {
	ExOpenGLContext glc;
	GLXFBConfig fbconfig;
	ExChooseFBconfig(&fbconfig);

	glc = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE, 0, 1);
	return glc;
}

ExOpenGLContext ExCreateGLContext(ExWin window, ExOpenGLContext shareContext) {
	ExOpenGLContext glc = NULL;
	ExOpenGLContext curglc;
	unsigned int vendor;
	unsigned int glxmaj, glxmin;
	unsigned int major;
	unsigned int minor;
	unsigned int contextflag;
	unsigned int contextprofile;

	XVisualInfo* vi; /*	Visual Info	*/
	int min;
	int maj;
	GLXFBConfig fbconfig;

	/*if windows doesn't support the opengl, than try to use */
	if (!glXQueryExtension(display, &min, &maj)) {
		ExError("OpenGL not supported by X server\n");
	}

	if (shareContext)
		curglc = ExGetCurrentOpenGLContext();

	/**/
	glXQueryVersion(display, &glxmaj, &glxmin);

	/*	Get Current Supported Version of OpenGL	or get user requested version*/
	if (!ExOpenGLGetAttribute(EX_OPENGL_MAJOR_VERSION, NULL)) {
		if (!ExGetOpenGLVersion(&major, &minor)) {
			/*	bad	*/
		}
	} else {
		if (shareContext == NULL) {
			major = ExOpenGLGetAttribute(EX_OPENGL_MAJOR_VERSION, NULL);
			minor = ExOpenGLGetAttribute(EX_OPENGL_MINOR_VERSION, NULL);
		}
		/*	get current binded opengl context version.*/
		else if (!ExGetOpenGLVersion(&major, &minor)) {

		}
	}

	/**/
	if (shareContext == NULL) {
		contextflag = ExOpenGLGetAttribute(EX_OPENGL_CONTEXT_FLAGS, NULL);
		contextprofile = ExOpenGLGetAttribute(EX_OPENGL_CONTEXT_PROFILE_MASK,
				NULL);
		if (!ExIsExtensionSupported(
				glXQueryExtensionsString(display, DefaultScreen(display)),
				"GLX_ARB_create_context_profile")) {
			contextprofile = EX_GL_CONTEXT_PROFILE_COMPATIBILITY;
		}
	} else {
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextprofile);
		glGetIntegerv(GL_CONTEXT_FLAGS, &contextflag);
	}

	int contextAttribs[] = {
	GLX_CONTEXT_MAJOR_VERSION_ARB, major,
	GLX_CONTEXT_MINOR_VERSION_ARB, minor,
#ifdef EX_DEBUG
			GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB | contextflag, /*  Debug TODO add hint*/
#else
			GLX_CONTEXT_FLAGS_ARB, contextflag,
#endif
			GLX_CONTEXT_PROFILE_MASK_ARB, contextprofile,
			None };

	switch (ExGetOpenGLVendor()) {
	case EX_AMD: {
		typedef int (*glXGetGPUIDsAMDProc)(unsigned int maxCount,
				unsigned int *ids);
		typedef GLXContext (*glXCreateAssociatedContextAMDProc)(unsigned int id,
				GLXContext share_context, const int *attribList);
		unsigned int gpuids[32];
		glXCreateAssociatedContextAMDProc glXCreateAssociatedContextAttribsAMD;
		glXGetGPUIDsAMDProc glXGetGPUIDsAMD;

		glXCreateAssociatedContextAttribsAMD = glXGetProcAddress(
				"glXCreateAssociatedContextAttribsAMD"); /*  AMD */
		glXGetGPUIDsAMD = glXGetProcAddress("glXGetGPUIDsAMD");
		if (ExIsExtensionSupported(
				glXQueryExtensionsString(display, DefaultScreen(display)),
				"GLX_AMD_gpu_association")) {
			glXGetGPUIDsAMD(sizeof(gpuids) / sizeof(gpuids[0]), gpuids);
			glc = glXCreateAssociatedContextAttribsAMD(gpuids[0], NULL, pixAtt);

		}
	}
		break;
	case EX_INTEL:
	case EX_NVIDIA:
	default: {

		if (ExIsExtensionSupported(
				glXQueryExtensionsString(display, DefaultScreen(display)),
				"GLX_ARB_create_context")) {
			typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,
					GLXFBConfig, GLXContext, Bool, const int*);
			glXCreateContextAttribsARBProc glXCreateContextAttribsARB =
					(glXCreateContextAttribsARBProc) glXGetProcAddress(
							(const GLubyte*) "glXCreateContextAttribsARB");

			if (glXCreateContextAttribsARB) {
				if (shareContext) {
					if (glXQueryContext(display, curglc, GLX_FBCONFIG_ID,
							&fbconfig) != Success) {

					} else
						ExChooseFBconfig(&fbconfig);
				} else
					ExChooseFBconfig(&fbconfig);

				glc = glXCreateContextAttribsARB(display, fbconfig,
						shareContext, True, contextAttribs);
				XSync(display, False);
			}
		} else {
			ExPrintf("GL_ARB_create_context not supported.\n");
			vi = glXChooseVisual(display, DefaultScreen(display), pixAtt);
			glc = glXCreateContext(display, vi, shareContext, True);
			XFree(vi);
		}
		/*

		 */
	}
		break;
	}

	glcdefault: /*	default opengl context	*/

	/**/
	if (!glc) {
		ExPrintf("Failed to create ARB Context.\n");
		glc = glXCreateNewContext(display, fbconfig, GLX_RGBA_TYPE,
				shareContext, True);
	}
	XSync(display, False);

	/**/
	if (!glXIsDirect(display, glc)) {
		fprintf(stderr, "Indirect GLX rendering context obtained.\n"); /*	a lose of performance.*/
	}

	return glc;
}

ExOpenGLContext ExCreateGLSharedContext(ExWin window, ExOpenGLContext glc) {
	return ExCreateGLContext(window, glc);
}

void ExOpenGLSetAttribute(unsigned int attr, int value) {
	pixAtt[PIXATTOFFSET + (2 * attr) + 1] = value;
}

int ExOpenGLGetAttribute(unsigned int attr, int* value) {
	if (value)
		value = (unsigned int) pixAtt[PIXATTOFFSET + (2 * attr) + 1];
	return pixAtt[PIXATTOFFSET + (2 * attr) + 1];
}

void ExOpenGLResetAttributes(void) {
	ExOpenGLSetAttribute(EX_OPENGL_RED_SIZE, 8);
	ExOpenGLSetAttribute(EX_OPENGL_GREEN_SIZE, 8);
	ExOpenGLSetAttribute(EX_OPENGL_BLUE_SIZE, 8);

	ExOpenGLSetAttribute(EX_OPENGL_DEPTH_SIZE, 24);
	ExOpenGLSetAttribute(EX_OPENGL_ALPHA_SIZE, 8);

	ExOpenGLSetAttribute(EX_OPENGL_DOUBLEBUFFER, EX_TRUE);

	ExOpenGLSetAttribute(EX_OPENGL_ACCUM_RED_SIZE, 0);
	ExOpenGLSetAttribute(EX_OPENGL_ACCUM_GREEN_SIZE, 0);
	ExOpenGLSetAttribute(EX_OPENGL_ACCUM_BLUE_SIZE, 0);
	ExOpenGLSetAttribute(EX_OPENGL_ACCUM_ALPHA_SIZE, 0);

	ExOpenGLSetAttribute(EX_OPENGL_ACCELERATED_VISUAL, 0);
	ExOpenGLSetAttribute(EX_OPENGL_STEREO, 0);
	ExOpenGLSetAttribute(EX_OPENGL_MULTISAMPLEBUFFERS, 0);
	ExOpenGLSetAttribute(EX_OPENGL_MULTISAMPLESAMPLES, 0);
	ExOpenGLSetAttribute(EX_OPENGL_FRAMEBUFFER_SRGB_CAPABLE, 0);
}

ExBoolean ExDestroyGLContext(ExWindowContext drawable, ExOpenGLContext glc) {
	ExBoolean hr = 1;

	if (!ExMakeGLCurrent(NULL, NULL)) {
		fprintf(stderr, "failed to make current Opengl NUll, NULL.\n");
		hr = 0;
	}
	glXDestroyContext(display, glc);
	return hr;
}

ExBoolean ExGLFullScreen(ExBoolean cdsfullscreen, ExWin window,
		unsigned int screenIndex, const int* screenRes) {
	int one = 1;
	XEvent xev = { 0 };
	ExSize size = { 0 };
	XWindowAttributes xwa;
	XSetWindowAttributes xattr = { 0 };
	Atom atom;

	/*	get resolution.	*/
	if (screenRes) {
		size.width = screenRes[0];
		size.height = screenRes[1];
	} else {
		if (cdsfullscreen)
			ExGetScreenSize(screenIndex, &size);
		else
			ExGetScreenSize(screenIndex, &size);
	}

	xattr.override_redirect = False;
	XChangeWindowAttributes(display, window, CWOverrideRedirect, &xattr);

	/**/

	atom = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", True);

	/**/
	XChangeProperty(display, window,
			XInternAtom(display, "_NET_WM_STATE", True),
			XA_ATOM, 32, PropModeReplace, (unsigned char*) &atom, 1);

	/*	Only for EGL.	*/
	/*
	 XChangeProperty (
	 display, window,
	 XInternAtom ( display, "_HILDON_NON_COMPOSITED_WINDOW", True ),
	 XA_INTEGER,  32,  PropModeReplace,
	 (unsigned char*) &one,  1);
	 */

	/*	Set fullscreen resolution.	*//*TODO	fix	*/
	if (ExSetScreenSize(screenIndex, size.width, size.height)) {
		/**/
	}
	ExShowWindow(window);

	//XF86VideoModeSwitchToMode(display, screenIndex, modes[bestMode]);
	Atom atoms[2] = { XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False),
			None };

	Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
	Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

	xev.type = ClientMessage;
	xev.xclient.window = window;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = cdsfullscreen ? 1 : 0;
	xev.xclient.data.l[1] = fullscreen;
	xev.xclient.data.l[2] = 0;

	XSendEvent(display, DefaultRootWindow(display),
	EX_FALSE,
	SubstructureNotifyMask | SubstructureRedirectMask, &xev);

	XResizeRequestEvent resize = { 0 };
	resize.display = display;
	resize.width = size.width;
	resize.height = size.height;
	resize.window = window;
	resize.type = ResizeRequest;
	XSendEvent(display, window, EX_FALSE, ResizeRedirectMask, &resize);

	return EX_TRUE;

}

void ExSetGLTransparent(ExWin window, unsigned int flag) {
	XTextProperty textprop = { 0 };
	XWMHints *startup_state;
	ExSize size;
	XSizeHints hints;

	if (window == NULL) {
		return;
	}

	/**/
	ExGetWindowSizev(window, &size);

	hints.x = 0;
	hints.y = 0;
	hints.width = size.width;
	hints.height = size.height;
	hints.flags = USPosition | USSize;

	/**/
	startup_state = XAllocClassHint();
	startup_state->initial_state = NormalState;
	startup_state->flags = StateHint;

	/**/
	XSetWMProperties(display, window, NULL, NULL,
	NULL, 0, &hints, startup_state,
	NULL);

	/**/
	XFree(startup_state);
}

const ExChar* ExGetOpenGLServerExtension(void) {
	return glXQueryServerString(display, DefaultScreen(display), GLX_EXTENSIONS);
}

const ExChar* ExGetOpenGLClientExtensions(void) {
	return glXGetClientString(display, GLX_EXTENSIONS);
}

int ExIsVendorAMD(void) {
	return strstr((const char*) glXGetClientString(display, GLX_VENDOR),
			"AMD") ? EX_TRUE : EX_FALSE;
}

int ExIsVendorNvidia(void) {
	return (strstr((const char*) glXGetClientString(display, GLX_VENDOR),
			"NVIDIA")) ? EX_TRUE : EX_FALSE;
}

int ExIsVendorintel(void) {
	return strstr((const char*) glXGetClientString(display, GLX_VENDOR),
			"INTEL") ? EX_TRUE : EX_FALSE;
}

ERESULT ExOpenGLSetVSync(ExBoolean enabled, ExWin window) {
	typedef void (*glXSwapintervalEXTProc)(Display*, GLXDrawable drawable,
			int intervale);
	glXSwapintervalEXTProc glXSwapintervalEXT =
			(glXSwapintervalEXTProc) GL_GET_PROC(
					(const GLubyte* )"glXSwapintervalEXT");
	if (glXSwapintervalEXT) {
		glXSwapintervalEXT(display, window, enabled);
		return EX_TRUE;
	} else
		return EX_FALSE;
}

void ExSwapBuffers(ExWin surface) {
	glXSwapBuffers(display, surface);
}
