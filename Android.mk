#
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS := -Wall -Wextra -Werror
LOCAL_SRC_FILES := ISimpleService.cpp
LOCAL_SHARED_LIBRARIES := libbinder libutils liblog
LOCAL_MODULE := libsimpleservice
LOCAL_MODULE_TAGS := optional
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk
include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_SRC_FILES := simpleservice.cpp
LOCAL_SHARED_LIBRARIES := libutils libsimpleservice libbinder libdl
LOCAL_MODULE := simpleservice
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := tinysvc.cpp
LOCAL_SHARED_LIBRARIES := libutils libbinder libdl
LOCAL_MODULE := tinysvc
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := tinyclient.cpp
LOCAL_SHARED_LIBRARIES := libutils libbinder libdl
LOCAL_MODULE := tinyclient
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := simpleclient.cpp
LOCAL_SHARED_LIBRARIES := libutils libsimpleservice libbinder libdl
LOCAL_MODULE := simpleclient
LOCAL_MODULE_TAGS := tests
include $(BUILD_EXECUTABLE)
