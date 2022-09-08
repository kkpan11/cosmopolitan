#ifndef COSMOPOLITAN_LIBC_RUNTIME_PTHREAD_H_
#define COSMOPOLITAN_LIBC_RUNTIME_PTHREAD_H_

#define PTHREAD_KEYS_MAX              64
#define PTHREAD_STACK_MIN             FRAMESIZE
#define PTHREAD_DESTRUCTOR_ITERATIONS 4

#define PTHREAD_BARRIER_SERIAL_THREAD 31337

#define PTHREAD_MUTEX_DEFAULT    PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_NORMAL     0
#define PTHREAD_MUTEX_RECURSIVE  1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_STALLED    0
#define PTHREAD_MUTEX_ROBUST     1

#define PTHREAD_PROCESS_DEFAULT PTHREAD_PROCESS_PRIVATE
#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED  1

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

/* clang-format off */
#define PTHREAD_ONCE_INIT {0}
#define PTHREAD_COND_INITIALIZER {PTHREAD_PROCESS_DEFAULT}
#define PTHREAD_BARRIER_INITIALIZER {PTHREAD_PROCESS_DEFAULT}
#define PTHREAD_RWLOCK_INITIALIZER {PTHREAD_PROCESS_DEFAULT}
#define PTHREAD_MUTEX_INITIALIZER {PTHREAD_MUTEX_DEFAULT, \
                                   PTHREAD_PROCESS_DEFAULT}
/* clang-format on */

typedef uintptr_t pthread_t;
typedef int pthread_id_np_t;
typedef char pthread_condattr_t;
typedef char pthread_rwlockattr_t;
typedef char pthread_barrierattr_t;
typedef unsigned pthread_key_t;
typedef void (*pthread_key_dtor)(void *);

typedef struct pthread_once_s {
  _Atomic(char) lock;
} pthread_once_t;

typedef struct pthread_spinlock_s {
  _Atomic(char) lock;
} pthread_spinlock_t;

typedef struct pthread_mutex_s {
  char type;
  char pshared;
  int reent;
  _Atomic(int) lock;
  _Atomic(int) waits;
} pthread_mutex_t;

typedef struct pthread_mutexattr_s {
  char type;
  char pshared;
} pthread_mutexattr_t;

typedef struct pthread_cond_s {
  char pshared;
  _Atomic(int) waits;
  _Atomic(unsigned) seq;
} pthread_cond_t;

typedef struct pthread_barrier_s {
  char pshared;
  int count;
  _Atomic(int) waits;
  _Atomic(int) popped;
} pthread_barrier_t;

typedef struct pthread_rwlock_s {
  char pshared;
  _Atomic(int) lock;
  _Atomic(int) waits;
} pthread_rwlock_t;

typedef struct pthread_attr_s {
  char detachstate;
  size_t stacksize;
  size_t guardsize;
  void *stackaddr;
  int scope;
  int schedpolicy;
  int inheritsched;
} pthread_attr_t;

int pthread_yield(void);
void pthread_exit(void *) wontreturn;
pthread_t pthread_self(void) pureconst;
pthread_id_np_t pthread_getthreadid_np(void);
int64_t pthread_getunique_np(pthread_t);
int pthread_setname_np(pthread_t, const char *);
int pthread_getname_np(pthread_t, char *, size_t);
int pthread_getattr_np(pthread_t, pthread_attr_t *);
int pthread_attr_init(pthread_attr_t *);
int pthread_attr_destroy(pthread_attr_t *);
int pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int pthread_attr_setdetachstate(pthread_attr_t *, int);
int pthread_attr_getguardsize(const pthread_attr_t *, size_t *);
int pthread_attr_setguardsize(pthread_attr_t *, size_t);
int pthread_attr_getinheritsched(const pthread_attr_t *, int *);
int pthread_attr_setinheritsched(pthread_attr_t *, int);
int pthread_attr_getschedpolicy(const pthread_attr_t *, int *);
int pthread_attr_setschedpolicy(pthread_attr_t *, int);
int pthread_attr_getscope(const pthread_attr_t *, int *);
int pthread_attr_setscope(pthread_attr_t *, int);
int pthread_attr_getstack(const pthread_attr_t *, void **, size_t *);
int pthread_attr_setstack(pthread_attr_t *, void *, size_t);
int pthread_attr_getstacksize(const pthread_attr_t *, size_t *);
int pthread_attr_setstacksize(pthread_attr_t *, size_t);
int pthread_create(pthread_t *, const pthread_attr_t *, void *(*)(void *),
                   void *);
int pthread_detach(pthread_t);
int pthread_cancel(pthread_t);
int pthread_join(pthread_t, void **);
int pthread_equal(pthread_t, pthread_t);
int pthread_once(pthread_once_t *, void (*)(void));
int pthread_spin_init(pthread_spinlock_t *, int);
int pthread_spin_destroy(pthread_spinlock_t *);
int pthread_spin_lock(pthread_spinlock_t *);
int pthread_spin_unlock(pthread_spinlock_t *);
int pthread_spin_trylock(pthread_spinlock_t *);
int pthread_mutexattr_init(pthread_mutexattr_t *);
int pthread_mutexattr_destroy(pthread_mutexattr_t *);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *, int *);
int pthread_mutexattr_settype(pthread_mutexattr_t *, int);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *, int *);
int pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutex_trylock(pthread_mutex_t *);
int pthread_mutex_destroy(pthread_mutex_t *);
int pthread_mutex_consistent(pthread_mutex_t *);
int pthread_condattr_init(pthread_condattr_t *);
int pthread_condattr_destroy(pthread_condattr_t *);
int pthread_condattr_setpshared(pthread_condattr_t *, int);
int pthread_condattr_getpshared(const pthread_condattr_t *, int *);
int pthread_cond_init(pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_destroy(pthread_cond_t *);
int pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_cond_signal(pthread_cond_t *);
int pthread_rwlockattr_init(pthread_rwlockattr_t *);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *, int *);
int pthread_rwlock_init(pthread_rwlock_t *, const pthread_rwlockattr_t *);
int pthread_rwlock_destroy(pthread_rwlock_t *);
int pthread_rwlock_rdlock(pthread_rwlock_t *);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int pthread_rwlock_wrlock(pthread_rwlock_t *);
int pthread_rwlock_trywrlock(pthread_rwlock_t *);
int pthread_rwlock_unlock(pthread_rwlock_t *);
int pthread_key_create(pthread_key_t *, pthread_key_dtor);
int pthread_key_delete(pthread_key_t);
int pthread_setspecific(pthread_key_t, void *);
void *pthread_getspecific(pthread_key_t);
int pthread_barrierattr_init(pthread_barrierattr_t *);
int pthread_barrierattr_destroy(pthread_barrierattr_t *);
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *, int *);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *, int);
int pthread_barrier_wait(pthread_barrier_t *);
int pthread_barrier_destroy(pthread_barrier_t *);
int pthread_barrier_init(pthread_barrier_t *, const pthread_barrierattr_t *,
                         unsigned);

#define pthread_spin_init(pSpin, multiprocess) ((pSpin)->lock = 0, 0)
#define pthread_spin_destroy(pSpin)            ((pSpin)->lock = -1, 0)
#if (__GNUC__ + 0) * 100 + (__GNUC_MINOR__ + 0) >= 407
extern const errno_t EBUSY;
#define pthread_spin_lock(pSpin)                                          \
  ({                                                                      \
    pthread_spinlock_t *_s = pSpin;                                       \
    while (__atomic_test_and_set(&_s->lock, __ATOMIC_SEQ_CST)) donothing; \
    0;                                                                    \
  })
#define pthread_spin_unlock(pSpin)                    \
  ({                                                  \
    pthread_spinlock_t *_s = pSpin;                   \
    __atomic_store_n(&_s->lock, 0, __ATOMIC_RELAXED); \
    0;                                                \
  })
#define pthread_spin_trylock(pSpin)                                 \
  ({                                                                \
    pthread_spinlock_t *_s = pSpin;                                 \
    __atomic_test_and_set(&_s->lock, __ATOMIC_SEQ_CST) ? EBUSY : 0; \
  })
#endif /* GCC 4.7+ */

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_RUNTIME_PTHREAD_H_ */
