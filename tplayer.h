#ifndef TPLAYER_H
#define TPLAYER_H

#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QByteArray>
#include <QApplication>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <glib.h>

#define LINK_SUCCESS	1
#define LINK_FAIL		0

#define SELECT_IMAGE  1
#define SELECT_VIDEO  2

#define	USE_POP_MODE	0	// 1: recreate all elements when changing image/video
#define MAX_IMAGE_FILE	100
#define MAX_VIDEO_FILE  100

#define debug_msg(fmt, ...)     qDebug(fmt, ##__VA_ARGS__);//printf(fmt, ##__VA_ARGS__)

#define CHECK_ELEMENT_CREATED(element, msg, goto_if_fail)   if(!element)		\
    {				\
        debug_msg("<%s> create failed", msg);   \
        goto goto_if_fail;	\
    }

// pipeline state
enum pipe_state {
    STATE_PLAYING,		// pipeline state PLAYING
    STATE_PREPARING,	// pipeline not prepared
    STATE_PAUSE,		// pipeline is READY
    STATE_STOP		// else
};

typedef struct _PipeElement {
    int state;
    char * edid;

    GMainLoop * loop;
    GstBus * bus;

    GstElement * pipeline;

    GstElement * source;
    GstElement * typefind;
    GstElement * queue;

    GstElement * menu_bin;
#if (CREATE_ON_PLAY == 0)
    GstElement * demux;
    GstElement * decode;
#endif	/* CREATE_ON_PLAY */

    GstElement * textoverlay;
    GstElement * caps;
    GstElement * sink;

    gboolean menu_flag;	// menu on/off flag
    gboolean end_flag;	// play stop flag
    gboolean timer_flag;// timer flag

    gint play_select;
    gint play_idx;		// play index
    char ** play_list;
    char * play_cnt;
    char * menu_img;		// menu image file path

    // Original event handler of Pad
    GstPadEventFunction f_event_handler;
} PipeElement;

typedef enum {
    PLAY_START,
    PLAY_STOP,
    PLAY_RESTART,
    PLAY_RESUME,
    PLAY_NEXT,
    PLAY_PREV
}play_type_t;

class TPlayer
{
public:
    PipeElement play_obj;
    char img_cnt=0;
    char video_cnt=0;
    char * image_list[MAX_IMAGE_FILE];
    char * video_list[MAX_VIDEO_FILE];
    typedef gboolean (TPlayer::*play_handler_t)(gpointer user_data);

    TPlayer(WId winid);
    ~TPlayer();

    static gboolean st_play_start(gpointer user_data)
    {return reinterpret_cast<TPlayer*>(user_data)->play_start(&(reinterpret_cast<TPlayer*>(user_data)->play_obj)); }
    static gboolean st_play_stop(gpointer user_data)
    {return reinterpret_cast<TPlayer*>(user_data)->play_stop(&(reinterpret_cast<TPlayer*>(user_data)->play_obj)); }
    gboolean play_start		(gpointer user_data);
    gboolean play_stop		(gpointer user_data);
    gboolean play_restart	(gpointer user_data);
    gboolean play_resume	(gpointer user_data);
    gboolean play_next		(gpointer user_data);
    gboolean play_prev		(gpointer user_data);
    gboolean play_image		(gpointer user_data);
    gboolean play_video		(gpointer user_data);

private:

    GstBusSyncReply my_bus_callback(GstBus *bus, GstMessage *message, void *obj);
    void pad_added_handler (GstElement *src, GstPad *new_pad, void *data);
    void pad_removed_handler (GstElement *src, GstPad *new_pad, void *data);
    void type_find_handler (GstElement *typefind, guint probability, GstCaps *caps, void *data);

    static void st_type_find_handler(GstElement *typefind, guint probability, GstCaps *caps, void * instance)
    {   reinterpret_cast<TPlayer*>(instance)->type_find_handler(typefind, probability, caps, instance);    }
    static void st_pad_removed_handler(GstElement *src, GstPad *new_pad, void * instance)
    {   reinterpret_cast<TPlayer*>(instance)->pad_removed_handler(src, new_pad, instance);    }
    static void st_pad_added_handler(GstElement *src, GstPad *new_pad, void * instance)
    {   reinterpret_cast<TPlayer*>(instance)->pad_added_handler(src, new_pad, instance);    }
    static GstBusSyncReply st_my_bus_callback(GstBus *bus, GstMessage *message, GstPipeline *play_pipeline, void * instance)
    {   return reinterpret_cast<TPlayer*>(instance)->my_bus_callback(bus, message, play_pipeline);    }

#if (CREATE_ON_PLAY == 0)
    GstElement * jpg_bin;
    GstElement * bmp_bin;
    GstElement * h264_bin;
    GstElement * mpeg_bin;
    GstElement * qtdemux;
    GstElement * matroskademux;
    GstElement * tsdemux;
    GstElement * mpegpsdemux;
    int all_bin_created = FALSE;

    void make_all_decode_bin(gpointer user_data, void * add_handler, void * remove_handler);
#endif
    int select_decode_bin(GstElement ** bin, char * type);
    int select_demux_bin(GstElement ** bin, char * type);

    int make_jpg_bin(GstElement ** bin);
    int make_bmp_bin(GstElement ** bin);
    int make_h264_bin(GstElement ** bin);
    int make_mpeg_bin(GstElement ** bin);


    int link_image_decode(gpointer user_data, char * type);
    int link_video_decode(gpointer user_data, const char * type, GstPad *new_pad);
    int link_video_demux(gpointer user_data, char * type);

};

#endif // TPLAYER_H
