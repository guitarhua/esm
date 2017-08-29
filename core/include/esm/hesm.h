#ifndef CORE_INCLUDE_ESM_HESM_H_
#define CORE_INCLUDE_ESM_HESM_H_

#include "esm/esm.h"

#define ESM_COMPLEX_STATE(_name, _parent) \
      static void esm_##_name##_entry(esm_t *const esm); \
      static void esm_##_name##_handle(esm_t *const esm, esm_signal_t *sig); \
      static void esm_##_name##_exit(esm_t *const esm); \
      static void esm_##_name##_init(esm_t *const esm); \
      static const esm_hstate_t esm_##_name##_state = { \
            .super = { \
                  .entry = esm_##_name##_entry, \
                  .handle = esm_##_name##_handle, \
                  .exit = esm_##_name##_exit, \
                  .name = #_name, \
      }, \
      .parent = &esm_##_parent##_state, \
      .init = esm_##_name##_init \
      }

#define ESM_LEAF_STATE(_name, _parent) \
      static void esm_##_name##_entry(esm_t *const esm); \
      static void esm_##_name##_handle(esm_t *const esm, esm_signal_t *sig); \
      static void esm_##_name##_exit(esm_t *const esm); \
      static const esm_lstate_t esm_##_name##_state = { \
            .super = { \
                  .entry = esm_##_name##_entry, \
                  .handle = esm_##_name##_handle, \
                  .exit = esm_##_name##_exit, \
                  .name = #_name, \
      }, \
      .parent = &esm_##_parent##_state, \
      }

#define ESM_COMPLEX_REGISTER(_type, _name, _init, _sigq_size) \
      static _type##_esm_t _name##_ctx = { \
            .esm = { \
                  .super = { \
                        .name = #_name, \
                        .id = esm_id_##_name, \
                        .subscribed = ESM_INIT_SUB, \
                        .curr_state = (esm_state_t *)&esm_##_init##_state, \
                        .sig_queue_size = _sigq_size, \
                        .sig_queue = (esm_signal_t[_sigq_size]){0}, \
            }, \
      }, \
      .cfg = &_name##_cfg \
      }; \
      esm_t * const _name##_esm \
      __attribute((__section__("esm_complex"))) \
      __attribute((__used__)) = (esm_t *)&_name##_ctx.esm;

typedef struct _hesm hesm_t;
typedef struct _hesmstate esm_hstate_t;

struct _hesmstate {
	esm_state_t super;
	struct _hesmstate const * const parent;
	void (*init)(esm_t *const esm);
};

typedef struct {
	esm_state_t super;
	struct _hesmstate const * const parent;
} esm_lstate_t;

struct _hesm {
	esm_t super;
};

extern const esm_hstate_t esm_top_state;

#endif /* CORE_INCLUDE_ESM_HESM_H_ */
