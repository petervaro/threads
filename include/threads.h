/* INFO **
** INFO */

/* Header guards */
#ifndef THREADS_H_3524374675182826
#define THREADS_H_3524374675182826 1

/*============================================================================*/
/* If standard threads.h is available */
#ifndef __STDC_NO_THREADS__
    #include <threads.h>
/*============================================================================*/
/* If a drop-in replacement required */
#else
    /* If the standard is lesser than C11 */
    #if __STDC__ < 201112L
        #error "'threads' is only available in standard ISO C11"
    #endif

    /*  Make sure the optional macro is undefined, so the user can saely check
        if the eatures of threads.h are available or not */
    #undef __STDC_NO_THREADS__
    /*  Include time.h as the standard specifies it at 7.26.1p1 */
    #include <time.h>
    /*  type  : struct timespec */

    /*========================================================================*/
    /*  If thread model is POSIX:
        The following declarations are the private interface of the threads
        library which supports the POSIX threads */
    #if defined unix        ||                                                 \
        defined __unix      ||                                                 \
        defined __unix__    ||                                                 \
        defined __linux__   ||                                                 \
        defined __FreeBSD__ ||                                                 \
        defined __CYGWIN__  ||                                                 \
        (defined __APPLE__ && defined __MACH__)

        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        /* Include POSIX headers */
        #include <pthread.h>
        /*  type  : pthread_once_t
                    pthread_cond_t
                    pthread_mutex_t
            const : PTHREAD_ONCE_INIT
            func  : pthread_once
                    pthread_mutex_destroy
                    pthread_cond_broadcast
                    pthread_cond_destroy
                    pthread_cond_init
                    pthread_cond_signal
                    pthread_cond_wait
                    pthread_mutex_lock */

        /*--------------------------------------------------------------------*/
        /* Call once */
        typedef pthread_once_t threads__once_flag;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define THREADS__ONCE_FLAG_INIT PTHREAD_ONCE_INIT
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__call_once(flag, func) pthread_once((flag), (func))

        /*--------------------------------------------------------------------*/
        /* Threads */
        typedef ___ threads__thrd_t;

        /*--------------------------------------------------------------------*/
        /* Mutual Exclusion */
        typedef pthread_mutex_t threads__mtx_t;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__mtx_destroy(mtx) \
            (pthread_mutex_destroy(mtx), (void)0)
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__mtx_init(threads__mtx_t *mtx,
                          int             type);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__mtx_lock(mtx) \
            (pthread_mutex_lock(mtx) ? thrd_error : thrd_success)
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__mtx_timedlock(threads__mtx_t        *restrict mtx,
                               const struct timespec *restrict ts);

        /*--------------------------------------------------------------------*/
        /* Condition variables */
        typedef pthread_cond_t threads__cnd_t;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__cnd_broadcast(cond) \
            (pthread_cond_broadcast(cond) ? thrd_error : thrd_success)
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__cnd_destroy(cond) \
            (pthread_cond_destroy(cond), (void)0)
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_init(cnd_t *cond);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__cnd_signal(cond) \
            (pthread_cond_signal(cond) ? thrd_error : thrd_success)
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_timedwait(cnd_t                 *restrict cond,
                               mtx_t                 *restrict mtx,
                               const struct timespec *restrict ts);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define threads__cnd_wait(cond, mtx) \
            (pthread_cond_wait((cond), (mtx)) ? thrd_error : thrd_success)

        /*--------------------------------------------------------------------*/
        /* Thread-local storage */
        #define thread_local _Thread_local
        #define THREADS__TSS_DTOR_ITERATIONS ___
        typedef ___ threads__tss_t;



    /*========================================================================*/
    /*  If thread model is windows:
        The following declarations are the private interface of the threads
        library which supports the Windows threads */
    #elif defined WIN32   ||                                                   \
          defined _WIN32  ||                                                   \
          defined __WIN32

        /*--------------------------------------------------------------------*/
        /* Call once */
        typedef ___ threads__once_flag;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        #define THREADS__ONCE_FLAG_INIT ___
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        void
        threads__call_once(threads__once_flag  *flag,
                           void               (*func)(void));

        /*--------------------------------------------------------------------*/
        /* Mutual Exclusion */
        typedef ___ threads__mtx_t;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        void
        threads__mtx_destroy(threads__mtx_t *mtx);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__mtx_init(threads__mtx_t *mtx,
                          int             type);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__mtx_lock(threads__mtx_t *mtx);

        /*--------------------------------------------------------------------*/
        /* Condition variables */
        typedef ___ threads__cnd_t;
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_broadcast(threads__cnd_t *cond);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        void
        threads__cnd_destroy(threads__cnd_t *cond);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_init(threads__cnd_t *cond);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_signal(threads__cnd_t *cond);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_timedwait(threads__cnd_t        *restrict cond,
                               threads__mtx_t        *restrict mtx,
                               const struct timespec *restrict ts);
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        int
        threads__cnd_wait(threads__cnd_t *cond,
                          threads__mtx_t *mtx);



    /*========================================================================*/
    /*  If the platform does not support POSIX, nor the Windows thread model
        throw a compile time error */
    #else
        #error "Currently 'threads' is not supporting this platform"
    #endif /* thread-model */



    /*========================================================================*/
    /*  The following aliases and redirections are the public interfaces of the
        threads library. Everything declared before -- that is, identifiers
        starts with `threads__` or `THREADS__` -- should not be used directly,
        as only the following identifiers are guaranteed to be conforming to the
        standard. */

    /*------------------------------------------------------------------------*/
    /* Call once */
    /* Holds a flag for use by call_once */
    typedef threads__once_flag once_flag;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Value that can be used to initialize an object of type once_flag */
    #define ONCE_FLAG_INIT THREADS__ONCE_FLAG_INIT

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `call_once` function uses the `once_flag` pointed to by `flag` to
        ensure that `func` is called exactly once, the first time the
        `call_once` function is called with that value of `flag`. Completion of
        an effective call to the `call_once` function synchronizes with all
        subsequent calls to the `call_once` function with the same value of
        `flag`.
        Prototype:
        void
        call_once(once_flag  *flag,
                  void      (*func)(void)) */
    #define call_once(flag, func) \
        threads__call_once((flag), (func))



    /*------------------------------------------------------------------------*/
    /* Condition variables */
    typedef threads__cnd_t cnd_t;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_broadcast` function unblocks all of the threads that are
        blocked on the condition variable pointed to by `cond` at the time of
        the call. If no threads are blocked on the condition variable pointed to
        by `cond` at the time of the call, the function does nothing.
        Returns:
        The `cnd_broadcast` function returns `thrd_success` on success, or
        `thrd_error` if the request could not be honored.
        Prototype:
        int
        cnd_broadcast(cnd_t *cond) */
    #define cnd_broadcast(cond) \
        threads__cnd_broadcast(cond)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_destroy` function releases all resources used by the condition
        variable pointed to by `cond`. The `cnd_destroy` function requires that
        no threads be blocked waiting for the condition variable pointed to by
        `cond`.
        Prototype:
        void
        cnd_destroy(cnd_t *cond) */
    #define cnd_destroy(cond) \
        threads__cnd_destroy(cond)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_init` function creates a condition variable. If it succeeds it
        sets the variable pointed to by `cond` to a value that uniquely
        identifies the newly created condition variable. A thread that calls
        `cnd_wait` on a newly created condition variable will block.
        Returns:
        The `cnd_init` function returns `thrd_success` on success, or
        `thrd_nomem` if no memory could be allocated for the newly created
        condition, or `thrd_error` if the request could not be honored.
        Prototype:
        int
        cnd_init(cnd_t *cond) */
    #define cnd_init(cond) \
        threads__cnd_init(cond)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_signal` function unblocks one of the threads that are blocked
        on the condition variable pointed to by `cond` at the time of the call.
        If no threads are blocked on the condition variable at the time of the
        call, the function does nothing and return success.
        Returns:
        The cnd_signal function returns thrd_success on success or thrd_error if
        the request could not be honored.
        Prototype:
        int
        cnd_signal(cnd_t *cond) */
    #define cnd_signal(cond) \
        threads__cnd_signal(cond)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_timedwait` function atomically unlocks the mutex pointed to by
        `mtx` and endeavors to block until the condition variable pointed to by
        `cond` is signaled by a call to `cnd_signal` or to `cnd_broadcast`, or
        until after the `TIME_UTC`-based calendar time pointed to by `ts`. When
        the calling thread becomes unblocked it locks the variable pointed to by
        `mtx` before it returns. The `cnd_timedwait` function requires that the
        mutex pointed to by `mtx` be locked by the calling thread.
        Returns:
        The `cnd_timedwait` function returns `thrd_success` upon success, or
        `thrd_timedout` if the time specified in the call was reached without
        acquiring the requested resource, or `thrd_error` if the request could
        not be honored.
        Prototype:
        int
        cnd_timedwait(cnd_t                 *restrict cond,
                      mtx_t                 *restrict mtx,
                      const struct timespec *restrict ts) */
    #define cnd_timedwait(cond, mtx, ts) \
        threads__cnd_timedwait((cond), (mtx), (ts))

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `cnd_wait` function atomically unlocks the mutex pointed to by `mtx`
        and endeavors to block until the condition variable pointed to by `cond`
        is signaled by a call to `cnd_signal` or to `cnd_broadcast`. When the
        calling thread becomes unblocked it locks the mutex pointed to by `mtx`
        before it returns. The `cnd_wait` function requires that the mutex
        pointed to by `mtx` be locked by the calling thread.
        Returns:
        The `cnd_wait` function returns `thrd_success` on success or
        `thrd_error` if the request could not be honored.
        Prototype:
        int
        cnd_wait(cnd_t *cond, mtx_t *mtx) */
    #define cnd_wait(cond, mtx) \
        threads__cnd_wait((cond), (mtx))



    /*------------------------------------------------------------------------*/
    /* Mutual Exclusion */
    typedef threads__mtx_t mtx_t;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Enumeration constants passed to `mtx_init` */
    enum
    {
        /*  Create a mutex object that supports
            neither timeout nor test and return */
        mtx_plain     = 1,
        /*  Create a mutex object that supports
            recursive locking */
        mtx_recursive = 2,
        /*  Create a mutex object that supports timeout */
        mtx_timed     = 4,
    };

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `mtx_destroy` function releases any resources used by the mutex
        pointed to by `mtx`. No threads can be blocked waiting for the mutex
        pointed to by `mtx`.
        Prototype:
        void
        mtx_destroy(mtx_t *mtx) */
    #define mtx_destroy(mtx) \
        threads__mtx_destroy(mtx)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `mtx_init` function creates a mutex object with properties indicated
        by type, which must have one of the six values:
        `mtx_plain`:
            for a simple non-recursive mutex,
        `mtx_timed`:
            for a non-recursive mutex that supports timeout,
        `mtx_plain` | `mtx_recursive`:
            for a simple recursive mutex, or
        `mtx_timed` | `mtx_recursive`:
            for a recursive mutex that supports timeout.
        If the `mtx_init` function succeeds, it sets the mutex pointed to by
        `mtx` to a value that uniquely identifies the newly created mutex.
        Returns:
        The `mtx_init` function returns `thrd_success` on success, or
        `thrd_error` if the request could not be honored.
        Prototype:
        int
        mtx_init(mtx_t *mtx, int type) */
    #define mtx_init(mtx, type) \
        threads__mtx_init((mtx), (type))

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `mtx_lock` function blocks until it locks the mutex pointed to by
        `mtx`. If the mutex is non-recursive, it shall not be locked by the
        calling thread. Prior calls to `mtx_unlock` on the same mutex shall
        synchronize with this operation.
        Returns:
        The `mtx_lock` function returns `thrd_success` on success, or
        `thrd_error` if the request could not be honored.
        Prototype:
        int
        mtx_lock(mtx_t *mtx) */
    #define mtx_lock(mtx) \
        threads__mtx_lock(mtx)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The `mtx_timedlock` function endeavors to block until it locks the mutex
        pointed to by `mtx` or until after the `TIME_UTC`-based calendar time
        pointed to by `ts`. The specified mutex shall support timeout. If the
        operation succeeds, prior calls to `mtx_unlock` on the same mutex shall
        synchronize with this operation.
        Returns:
        The `mtx_timedlock` function returns `thrd_success` on success, or
        `thrd_timedout` if the time specified was reached without acquiring the
        requested resource, or `thrd_error` if the request could not be honored.
        Prototype:
        int
        mtx_timedlock(mtx_t                 *restrict mtx,
                      const struct timespec *restrict ts) */
    #define mtx_timedlock(mtx, ts) \
        threads__mtx_timedlock((mtx), (ts))



    /*------------------------------------------------------------------------*/
    /* Threads */
    /*  The function pointer that is passed to thrd_create to create a new
        thread */
    typedef int  (*thrd_start_t)(void*);

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    enum
    {
        /*  Returned by a function to indicate that
            the requested operation succeeded */
        thrd_success,
        /*  Returned by a function to indicate that
            the requested operation failed because it
            was unable to allocate memory */
        thrd_nomem,
        /*  Returned by a timed wait function to indicate
            that the time specified in the call was reached
            without acquiring the requested resource */
        thrd_timedout,
        /*  Returned by a function to indicate that the
            requested operation failed because a resource
            requested by a test and return function is
            already in use */
        thrd_busy,
        /*  Returned by a function to indicate that
            the requested operation failed */
        thrd_error,
    };



    /*------------------------------------------------------------------------*/
    /* Thread-local storage */
    typedef threads__tss_t tss_t;

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  The function pointer used for a destructor for a thread-specific storage
        pointer */
    typedef void (*tss_dtor_t)(void*);

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /*  Expands to an integer constant expression representing the maximum
        number of times that destructors will be called when a thread
        terminates */
    #define TSS_DTOR_ITERATIONS THREADS__TSS_DTOR_ITERATIONS

#endif /* __STDC_NO_THREADS__ */
#endif /* THREADS_H_3524374675182826 */
