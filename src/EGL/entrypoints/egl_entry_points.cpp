// A sample EGL implement

#include <dlfcn.h>
#include <cstdlib>
#include <cstring>
#include "OpenGL/entrypoints/egl_Interface.h"
#include "EGL/entrypoints/egl_entry_points.h"
#include <EGL/egl.h>

#include "EGL/eglDisplay.h"
#include "EGL/eglContext.h"
#include "EGL/eglSurface.h"
#include "EGL/eglConfig.h"
#include "EGL/globals.h"

#include "Common/globals.h"


#if defined(USE_COMBINED_EGL_OPENGL)
    extern egl_Interface_t EGLInterface;
    egl_Interface_t *m_EGLInterface = nullptr;
#else
    #define VKGL_LIB_NAME "libVKGL32.so"
    egl_Interface_t *m_EGLInterface = nullptr;
    void *			m_libVKGL_handle = nullptr;
#endif



EGLAPI EGLDisplay EGLAPIENTRY
eglGetDisplay(EGLNativeDisplayType display)
{
    //FUN_ENTRY(DEBUG_DEPTH);
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    	
	EGL::eglDisplay_t* eglDisplay = new EGL::eglDisplay_t();
	
    return (EGLDisplay)eglDisplay;
}

EGLAPI EGLint EGLAPIENTRY
eglGetError(void)
{
    //THREAD_EXEC_RETURN(GetError());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    return EGL::get_current_egl_error();
}

EGLAPI EGLBoolean EGLAPIENTRY
eglBindAPI(EGLenum api)
{
    //THREAD_EXEC_RETURN(BindAPI(api));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLenum EGLAPIENTRY
eglQueryAPI(void)
{
    //THREAD_EXEC_RETURN(QueryAPI());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    return EGL_OPENGL_ES_API;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglWaitClient(void)
{
    //THREAD_EXEC_RETURN(WaitClient());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    
    m_EGLInterface->p_finish(((EGL::eglContext_t *)eglGetCurrentContext() )->get_gl_context_p() );
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglReleaseThread(void)
{
    //THREAD_EXEC_RETURN(ReleaseThread());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLContext EGLAPIENTRY
eglGetCurrentContext(void)
{
    //THREAD_EXEC_RETURN(GetCurrentContext());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglDisplay_t* eglDisplay = (EGL::eglDisplay_t*)EGL::get_current_display();
    
    EGL::eglContext_t *egl_ctx = (EGL::eglContext_t *)( eglDisplay->get_current_bind_egl_context_p() );
    
    return (EGLContext)egl_ctx;
}

EGLAPI EGLSurface EGLAPIENTRY
eglGetCurrentSurface(EGLint readdraw)
{
    //THREAD_EXEC_RETURN(GetCurrentSurface(readdraw));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglDisplay_t* eglDisplay = (EGL::eglDisplay_t*)EGL::get_current_display();
    
    EGL::eglContext_t *egl_ctx = (EGL::eglContext_t *)( eglDisplay->get_current_bind_egl_context_p() );
    
    EGL::eglSurface_t *egl_surf = (EGL::eglSurface_t *)( egl_ctx->get_egl_surface_p() );
    
    return (EGLSurface)egl_surf;
}

EGLAPI EGLDisplay EGLAPIENTRY
eglGetCurrentDisplay(void)
{
    //THREAD_EXEC_RETURN(GetCurrentDisplay());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglDisplay_t* eglDisplay = (EGL::eglDisplay_t*)EGL::get_current_display();
    
    return eglDisplay;
}

EGLAPI EGLContext EGLAPIENTRY
eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    //THREAD_EXEC_RETURN(CreateContext(dpy, config, share_context, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglContext_t *egl_ctx = new EGL::eglContext_t();
    
    uint32_t in_n_alpha_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_ALPHA_SIZE);
    uint32_t in_n_blue_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_BLUE_SIZE);
    uint32_t in_n_depth_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_DEPTH_SIZE);
    uint32_t in_n_green_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_GREEN_SIZE);
    uint32_t in_n_red_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_RED_SIZE);
    uint32_t in_n_stencil_bits = EGL::Config::get_config_value_from_attrib ((int*)config, EGL_STENCIL_SIZE);
    
    egl_ctx->set_pixel_format_reqs(  in_n_alpha_bits,
                                  in_n_blue_bits,
                                  in_n_depth_bits,
                                  in_n_green_bits,
                                  in_n_red_bits,
                                  in_n_stencil_bits);
    
    return (EGLContext)egl_ctx;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    //THREAD_EXEC_RETURN(DestroyContext(dpy, ctx));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglContext_t *egl_ctx = (EGL::eglContext_t*)ctx;
    if (egl_ctx == nullptr) return EGL_SUCCESS;
    
    if (egl_ctx->get_gl_context_p() )
    {
        m_EGLInterface->p_destroy_gl_context(egl_ctx->get_gl_context_p() );
    }
    
    if (egl_ctx->get_vk_backend_p() )
    {
        m_EGLInterface->p_destroy_vk_backend(egl_ctx->get_vk_backend_p() );
    }
    
    EGL::eglSurface_t *egl_surf = (EGL::eglSurface_t*)egl_ctx->get_egl_surface_p();
    if (egl_surf) {
    	egl_surf->set_egl_context_p(nullptr);
    }
    
    delete egl_ctx;
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    //THREAD_EXEC_RETURN(MakeCurrent(dpy, draw, read, ctx));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    /*auto egl_dpy = (EGL::eglDisplay_t*)dpy;
    
    auto egl_new_ctx = (EGL::eglContext_t*)ctx;
    auto egl_old_ctx = (EGL::eglContext_t*)nullptr;
    
    auto egl_new_surf = (EGL::eglSurface_t*)draw;
    auto egl_old_surf = (EGL::eglSurface_t*)nullptr;
    
    auto new_window = (void*)nullptr;
    auto old_window = (void*)nullptr;
    
    if (egl_new_ctx != nullptr &&
    	egl_new_surf != nullptr)
    {
    	egl_old_ctx = (EGL::eglContext_t*)egl_new_surf->get_egl_context_p();
    	egl_old_surf = (EGL::eglSurface_t*)egl_new_ctx->get_egl_surface_p();
    	
    	if (egl_old_surf) old_window = egl_old_surf->get_window();
    	if (egl_new_surf) new_window = egl_new_surf->get_window();
    	
    	{
	    	egl_new_ctx->set_egl_surface_p(egl_new_surf);
	    	
    	    void* vk_backend_p = m_EGLInterface->p_create_vk_backend(egl_new_ctx);
    
            void* gl_context_p = m_EGLInterface->p_create_gl_context(egl_new_ctx, vk_backend_p);
            
            m_EGLInterface->p_set_vk_backend_gl_context(gl_context_p, vk_backend_p);
            
            egl_new_ctx->set_vk_backend_p(vk_backend_p);
            egl_new_ctx->set_gl_context_p(gl_context_p);
        }
        
    	if (egl_old_ctx != egl_new_ctx &&
    		egl_old_ctx != nullptr)
    	{
    		void* old_vk_backend_p = egl_old_ctx->get_vk_backend_p();
    		
    		m_EGLInterface->p_destroy_vk_surface_swapchain(old_vk_backend_p, new_window);
    		
    		egl_old_ctx->set_egl_surface_p(nullptr);
    	}
    	else
    	{
    	    void* new_vk_backend_p = egl_new_ctx->get_vk_backend_p();
    	    
    	    if (egl_old_ctx == nullptr)
    	    {
        		m_EGLInterface->p_create_vk_surface_swapchain(new_vk_backend_p, new_window);
        	}
        	
        	if (egl_old_ctx == egl_new_ctx)
        	{
    		    m_EGLInterface->p_recreate_vk_surface_swapchain(new_vk_backend_p, new_window);
    		}
    	}
    	
    	egl_new_surf->set_egl_context_p(egl_new_ctx);
    }
    
    egl_dpy->set_current_bind_egl_context_p(egl_new_ctx);
    
    m_EGLInterface->p_make_current(egl_new_ctx->get_gl_context_p() );*/
    
    return EGL_TRUE;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
    //THREAD_EXEC_RETURN(QueryContext(dpy, ctx, attribute, value));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglWaitGL(void)
{
    //THREAD_EXEC_RETURN(WaitGL());
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);

    //TODO
    
    m_EGLInterface->p_finish( ((EGL::eglContext_t *)eglGetCurrentContext())->get_gl_context_p() );
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglWaitNative(EGLint engine)
{
    //THREAD_EXEC_RETURN(WaitNative(engine));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);

    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    //DRIVER_EXEC_RETURN(dpy, Initialize(dpy, major, minor));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGLBoolean result = EGL_SUCCESS;
    char *error = NULL;
    
    #if defined(USE_COMBINED_EGL_OPENGL)
    	m_EGLInterface = &EGLInterface;
    #else
        m_libVKGL_handle = dlopen(VKGL_LIB_NAME, RTLD_NOW);
        
        if (m_libVKGL_handle == nullptr) {
        	error = dlerror();
        	vkgl_printf("VKGL_EGL: %s", error);
        	error = dlerror();
        	result = EGL_FALSE;
        }
        
        m_EGLInterface = (egl_Interface_t *)dlsym(m_libVKGL_handle, "EGLInterface");
        
        if (m_EGLInterface == nullptr) {
        	error = dlerror();
        	vkgl_printf("VKGL_EGL: %s", error);
        	error = dlerror();
        	result = EGL_FALSE;
        }
    #endif
    
    if (major) *major = 1;
    if (minor) *minor = 4;
    
    
    EGL::eglDisplay_t* eglDisplay = (EGL::eglDisplay_t*)dpy;
    
    void* old_tls_ptr = EGL::get_current_display();
    
    eglDisplay->set_old_tls_ptr(old_tls_ptr);
    
    EGL::set_current_display( eglDisplay );
    
    
    return result;
    
}

EGLAPI EGLBoolean EGLAPIENTRY
eglTerminate(EGLDisplay dpy)
{
    //DRIVER_EXEC(dpy, Terminate(dpy));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    //TODO
    #if defined(USE_COMBINED_EGL_OPENGL)
    	m_EGLInterface = nullptr;
    #else
        dlclose(m_libVKGL_handle);
    #endif
    
    
    EGL::eglDisplay_t* eglDisplay = (EGL::eglDisplay_t*)dpy;
    
    void* old_tls_ptr = eglDisplay->get_old_tls_ptr();
        
    EGL::set_current_display( (EGL::eglDisplay_t*)old_tls_ptr );
    
    delete eglDisplay;
    
    
    return EGL_SUCCESS;
}

EGLAPI const char * EGLAPIENTRY
eglQueryString(EGLDisplay dpy, EGLint name)
{
    //FUN_ENTRY(DEBUG_DEPTH);
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);

    switch(name) {
    case EGL_CLIENT_APIS:   return "EGL_OPENGL_ES_API EGL_OPENGL_API"; break;
    case EGL_VENDOR:        return "VKGL"; break;
    case EGL_VERSION:       return "1.4"; break;
#ifdef VK_USE_PLATFORM_ANDROID_KHR
    case EGL_EXTENSIONS:    return "EGL_KHR_gl_texture_2D_image EGL_KHR_gl_renderbuffer_image"; break;
#else
    case EGL_EXTENSIONS:    return ""; break;
#endif
    default:                return ""; break;
    }

    return "\0";
}

EGLAPI EGLBoolean EGLAPIENTRY
eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    //DRIVER_EXEC_RETURN(dpy, GetConfigs(dpy, configs, config_size, num_config));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::Config::get_configs_for_attribs ((int**)configs, config_size, num_config, nullptr);
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    //DRIVER_EXEC_RETURN(dpy, ChooseConfig(dpy, attrib_list, configs, config_size, num_config));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::Config::get_configs_for_attribs ((int**)configs, config_size, num_config, (int*)attrib_list);
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
    //DRIVER_EXEC_RETURN(dpy, GetConfigAttrib(dpy, config, attribute, value));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    int out_value = EGL::Config::get_config_value_from_attrib ((int*)config, attribute);
    
    if (value) *value = out_value;
    
    return EGL_SUCCESS;
}

EGLAPI EGLSurface EGLAPIENTRY
eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreateWindowSurface(dpy, config, win, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglSurface_t *egl_surf = new EGL::eglSurface_t();
    
    egl_surf->set_window(win);
    
    return (EGLSurface)egl_surf;
}

EGLAPI EGLSurface EGLAPIENTRY
eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreatePbufferSurface(dpy, config, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_NO_SURFACE;
}

EGLAPI EGLSurface EGLAPIENTRY
eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreatePixmapSurface(dpy, config, pixmap, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_NO_SURFACE;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    //DRIVER_EXEC_RETURN(dpy, DestroySurface(dpy, surface));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    EGL::eglSurface_t *egl_surf = (EGL::eglSurface_t*)surface;
    if (egl_surf == nullptr) return EGL_SUCCESS;
    
    EGL::eglContext_t *egl_ctx = (EGL::eglContext_t*)egl_surf->get_egl_context_p();
    if (egl_ctx) {
    	m_EGLInterface->p_destroy_vk_surface_swapchain(egl_ctx->get_vk_backend_p(), nullptr);
    	
    	egl_ctx->set_egl_surface_p(nullptr);
    }
    
    delete egl_surf;
    
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
    //DRIVER_EXEC_RETURN(dpy, QuerySurface(dpy, surface, attribute, value));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLSurface EGLAPIENTRY
eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreatePbufferFromClientBuffer(dpy, buftype, buffer, config, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_NO_SURFACE;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
    //DRIVER_EXEC_RETURN(dpy, SurfaceAttrib(dpy, surface, attribute, value));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    //DRIVER_EXEC_RETURN(dpy, BindTexImage(dpy, surface, buffer));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    //DRIVER_EXEC_RETURN(dpy, ReleaseTexImage(dpy, surface, buffer));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
    //DRIVER_EXEC_RETURN(dpy, SwapInterval(dpy, interval));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    //DRIVER_EXEC_RETURN(dpy, SwapBuffers(dpy, surface));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    auto result = EGL_FALSE;
    
    auto egl_surf = (EGL::eglSurface_t*)surface;
    
    if (egl_surf)
    {
    	auto egl_ctx = (EGL::eglContext_t*)(egl_surf->get_egl_context_p() );
    	
    	if (egl_ctx)
    	{
    		void* gl_context_p = egl_ctx->get_gl_context_p();
    		
    		m_EGLInterface->p_swap_buffers(gl_context_p);
    		
    		result = EGL_SUCCESS;
    	}
    }
    
    return result;
}

EGLAPI EGLBoolean EGLAPIENTRY
eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
    //DRIVER_EXEC_RETURN(dpy, CopyBuffers(dpy, surface, target));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
    
    //TODO
    return EGL_SUCCESS;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY
eglGetProcAddress(const char *procname)
{
    std::string real_func_name = procname;
    void *proc = nullptr;

    proc = dlsym(RTLD_DEFAULT, real_func_name.c_str());

    if (!proc) {
        printf("Failed to get EGL or OpenGL function: %s\n", real_func_name.c_str());
        return nullptr;
    }
    
    // 将 void* 显式转换为函数指针类型
    return reinterpret_cast<__eglMustCastToProperFunctionPointerType>(proc);
}

//TODO
/*
EGLAPI EGLImageKHR EGLAPIENTRY
eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreateImageKHR(dpy, ctx, target, buffer, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
}

EGLAPI EGLBoolean EGLAPIENTRY
eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
    //DRIVER_EXEC_RETURN(dpy, DestroyImageKHR(dpy, image));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
}

//TODO: Implement the KHR_fence_sync extension
EGLAPI EGLSyncKHR EGLAPIENTRY
eglCreateSyncKHR(EGLDisplay dpy, EGLenum type, const EGLint *attrib_list)
{
    //DRIVER_EXEC_RETURN(dpy, CreateSyncKHR(dpy, type, attrib_list));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
}

EGLAPI EGLBoolean EGLAPIENTRY
eglDestroySyncKHR(EGLDisplay dpy, EGLSyncKHR sync)
{
    //DRIVER_EXEC_RETURN(dpy, DestroySyncKHR(dpy, sync));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
}

EGLAPI EGLint EGLAPIENTRY
eglClientWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout)
{
    //DRIVER_EXEC_RETURN(dpy, ClientWaitSyncKHR(dpy, sync, flags, timeout));
    
    FUN_ENTRY_GLAPI_CALL(DEBUG_DEPTH);
    FUN_ENTRY(DEBUG_DEPTH);
}
*/
