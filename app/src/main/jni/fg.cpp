// Required
#include <jni.h>

// We'll likely want these
#include <vector>
#include <string>

// Get any GNU Radio headers
#include <gnuradio/top_block.h>
#include <gnuradio/blocks/null_source.h>
#include <gnuradio/blocks/throttle.h>
#include <gnuradio/blocks/null_sink.h>
// Other block headers next

// Declare the global virtual machine and top-block objects
JavaVM *vm;
gr::top_block_sptr tb;

extern "C" {

JNIEXPORT void JNICALL
Java_org_gnuradio_grtemplate_MainActivity_FgInit(JNIEnv* env,
                                                 jobject thiz)
{
  GR_INFO("fg", "FgInit Called");

  // Declare our GNU Radio blocks
  gr::blocks::null_source::sptr src;
  gr::blocks::throttle::sptr thr;
  gr::blocks::null_sink::sptr snk;

  // Construct the objects for every block in the flwograph
  tb = gr::make_top_block("fg");
  src = gr::blocks::null_source::make(sizeof(gr_complex));
  thr = gr::blocks::throttle::make(sizeof(gr_complex), 10000);
  snk = gr::blocks::null_sink::make(sizeof(gr_complex));

  // Connect up the flowgraph
  tb->connect(src, 0, thr, 0);
  tb->connect(thr, 0, snk, 0);
}

JNIEXPORT void JNICALL
Java_org_gnuradio_grtemplate_MainActivity_FgStart(JNIEnv* env,
                                                  jobject thiz)
{
  GR_INFO("fg", "FgStart Called");
  tb->start();
}

JNIEXPORT void JNICALL
Java_org_gnuradio_grtemplate_MainActivity_FgStop(JNIEnv* env,
                                                 jobject thiz)
{
  GR_INFO("fg", "FgStop Called");
  tb->stop();
  tb->wait();
  GR_INFO("fg", "FgStop Exited");
}

JNIEXPORT jstring JNICALL
Java_org_gnuradio_grtemplate_MainActivity_FgRep(JNIEnv* env,
                                                jobject thiz)
{
  return env->NewStringUTF(tb->edge_list().c_str());
}

}
