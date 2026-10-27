#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int lock_state;
} custom_spinlock_t;

void spin_lock_init(custom_spinlock_t *lock) {
    lock->lock_state = 0;
}

void spin_lock(custom_spinlock_t *lock) {
    while (__atomic_test_and_set(&(lock->lock_state), __ATOMIC_ACQUIRE)) {
        // Активное ожидание (spin)
        __builtin_ia32_pause();
    }
}

void spin_unlock(custom_spinlock_t *lock) {
    __atomic_clear(&(lock->lock_state), __ATOMIC_RELEASE);
}

int main() {
    printf('=== PR-6: Custom Spinlock & ThreadSanitizer Verification ===\n');
    custom_spinlock_t spl;
    spin_lock_init(&spl);
    spin_lock(&spl);
    printf('Critical section acquired via atomic test-and-set.\n');
    spin_unlock(&spl);
    return 0;
}