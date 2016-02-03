/* INFO **
** INFO */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include standard headers */
#include <stddef.h>
/*  const : NULL */
#include <time.h>
/*  type  : struct timespec */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
/* Include threads headers */
#include "threads/threads.h"
/*  const : thrd_success
            thrd_nomem
            thrd_timedout
            thrd_budy
            thrd_error
            mtx_recursive
    type  : threads__once_flag
            threads__cnd_t
            threads__mtx_t */




/*============================================================================*/
/* If thread model is POSIX */
#if defined unix        ||                                                     \
    defined __unix      ||                                                     \
    defined __unix__    ||                                                     \
    defined __linux__   ||                                                     \
    defined __FreeBSD__ ||                                                     \
    defined __CYGWIN__  ||                                                     \
    (defined __APPLE__ && defined __MACH__)

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    /* Include POSIX headers */
    #include <pthread.h>
    /*  type  : pthread_mutexattr_t
        const : ENOMEM
                ETIMEDOUT
                PTHREAD_MUTEX_NORMAL
                PTHREAD_MUTEX_RECURSIVE
        func  : pthread_cond_init
                pthread_cond_timedwait
                pthread_mutexattr_init
                pthread_mutexattr_settype
                pthread_mutexattr_destroy
                pthread_mutex_init */



    /*------------------------------------------------------------------------*/
    int
    threads__cnd_init(threads__cnd_t *cond)
    {
        /* Convert errors to standard ones */
        switch (pthread_cond_init(cond, NULL))
        {
            case 0      : return thrd_success;
            case ENOMEM : return thrd_nomem;
            default     : return thrd_error;
        }
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__cnd_timedwait(threads__cnd_t        *restrict cond,
                           threads__mtx_t        *restrict mtx,
                           const struct timespec *restrict ts)
    {
        /* Convert errors to standard ones */
        switch (pthread_cond_timedwait(cond, mtx, ts))
        {
            case 0         : return thrd_success;
            case ETIMEDOUT : return thrd_timedout;
            default        : return thrd_error;
        }
    }



    /*------------------------------------------------------------------------*/
    int
    threads__mtx_init(threads__mtx_t *mtx,
                      int             type)
    {
        /* Local variables */
        pthread_mutexattr_t attr;

        /* Create mutex attribute */
        if (pthread_mutexattr_init(&attr)
            return thrd_error;

        /* Set proper type to mutex attribute */
        if (pthread_mutexattr_settype(
                &attr,
                (type & mtx_recursive) ? PTHREAD_MUTEX_RECURSIVE
                                       : PTHREAD_MUTEX_NORMAL))
            goto Error;

        /* Set attributes to mutex */
        if (pthread_mutex_init(mtx, &attr))
            goto Error;

        /* Destroy mutex attribute */
        if (pthread_mutexattr_destroy(&attr);
            return thrd_error;

        /* If everything went fine */
        return thrd_success;

        /* If there was an error */
        Error:
            pthread_mutexattr_destroy(&attr);
            return thrd_error;
    }

    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__mtx_timedlock(threads__mtx_t        *restrict mtx,
                           const struct timespec *restrict ts)
    {
        /* Convert errors to standard ones */
        switch (pthread_mutex_timedlock(mtx, ts))
        {
            case 0         : thrd_success;
            case ETIMEDOUT : thrd_timedout;
            default        : thrd_error;
        }
    }




/*============================================================================*/
/* If thread model is windows */
#elif defined WIN32   ||                                                       \
      defined _WIN32  ||                                                       \
      defined __WIN32

    /*------------------------------------------------------------------------*/
    void
    threads__call_once(threads__once_flag  *flag,
                       void               (*func)(void))
    {
        (void)flag;
        (void)func;
    }



    /*------------------------------------------------------------------------*/
    int
    threads__cnd_broadcast(threads__cnd_t *cond)
    {
        (void)cond;
        return thrd_success;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    void
    threads__cnd_destroy(threads__cnd_t *cond)
    {
        (void)cond;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__cnd_init(threads__cnd_t *cond)
    {
        (void)cond;
        return thrd_success;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__cnd_signal(threads__cnd_t *cond)
    {
        (void)cond;
        return thrd_success;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__cnd_timedwait(threads__cnd_t        *restrict cond,
                           threads__mtx_t        *restrict mtx,
                           const struct timespec *restrict ts)
    {
        (void)cond;
        (void)mtx;
        (void)ts;
        return thrd_success;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__cnd_wait(threads__cnd_t *cond,
                      threads__mtx_t *mtx)
    {
        (void)cond;
        (void)mtx;
        return thrd_success;
    }



    /*------------------------------------------------------------------------*/
    void
    threads__mtx_destroy(threads__mtx_t *mtx)
    {
        (void)mtx;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__mtx_init(threads__mtx_t *mtx,
                      int             type)
    {
        (void)mtx;
        (void)type;
        return thrd_success;
    }


    /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
    int
    threads__mtx_lock(threads__mtx_t *mtx)
    {
        (void)mtx;
        return thrd_success;
    }


#endif /* thread-model */
