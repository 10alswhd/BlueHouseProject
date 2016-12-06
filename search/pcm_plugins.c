/**
 * List ALSA pcm plugins.
 *
 * This code is based on code I saw in PortAudio, which is under the MIT license.
 * http://portaudio.com/trac/browser/portaudio/trunk/src/hostapi/alsa/pa_linux_alsa.c
 *
 * Note that the method used here is quite different to detecting hw devices,
 * which iterates over cards, devices and subdevices.
 *
 * gcc -o pcm_plugins pcm_plugins.c -lasound
 */

#include <stdio.h>
#include <alsa/asoundlib.h>

int main() {
    int result;

    snd_config_update();

    snd_config_t *top_node = NULL;
    result = snd_config_search(snd_config, "pcm", &top_node);
    if (result < 0) {
        fprintf(stderr, "snd_config_search error: %s\n", snd_strerror(result));
        return 1;
    }

    snd_config_iterator_t i, next;
    snd_config_for_each(i, next, top_node) {
        snd_config_t *n = snd_config_iterator_entry(i);

        snd_config_t *sct_type = NULL;
        result = snd_config_search(n, "type", &sct_type);
        if (result < 0) {
            if (result == -ENOENT) {
                printf("No type found\t");
            } else {
                fprintf(stderr, "snd_config_search error: %s\n", snd_strerror(result));
                return 1;
            }
        } else {
            const char *str_type;
            result = snd_config_get_string(sct_type, &str_type);
            if (result < 0) {
                fprintf(stderr, "snd_config_get_string error: %s\n", snd_strerror(result));
                return 1;
            }
            printf("Type: %s\t", str_type);
        }

        const char *str_id;
        result = snd_config_get_id(n, &str_id);
        if (result < 0) {
            fprintf(stderr, "snd_config_get_id error: %s\n", snd_strerror(result));
            return 1;
        }
        printf("ID: %s\n", str_id);
    }

    return 0;
}
