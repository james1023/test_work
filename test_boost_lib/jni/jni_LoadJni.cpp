//
//  jni_LoadJni.cpp
//  test_boost_lib
//
//  Created by james on 1/29/15.
//  Copyright (c) 2015 james. All rights reserved.
//

#include "jni_LoadJni.h"
#include "interface_lib.h"
#include "test_boost_lib.h"
#include <string>

JNIEXPORT jstring JNICALL Java_jni_LoadJni_get(JNIEnv *env, jobject obj, jint in)
{
    std::string get_str;
    get_str = get(in);
    
    return env->NewStringUTF(get_str.c_str());
    
    //return env->NewStringUTF("james102");
}