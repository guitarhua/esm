#ifndef INCLUDE_SIGNALS_H_
#define INCLUDE_SIGNALS_H_

#define ESM_SIGNALS \
		ESM_SIGNAL(tmout) \
		ESM_SIGNAL(button)

#define ESM_IDS \
      ESM_ID(debouncer) \
      ESM_ID(pelican)

typedef struct
{
} esm_sig_params_t;

#endif /* INCLUDE_SIGNALS_H_ */
