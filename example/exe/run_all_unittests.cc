// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/bind.h"
#include "base/test/launcher/unit_test_launcher.h"
#include "base/test/multiprocess_test.h"
#include "base/test/test_io_thread.h"
#include "base/test/test_suite.h"
#include "build/build_config.h"

#if defined(OS_MACOSX) && !defined(OS_IOS)
#include "base/mac/mach_port_broker.h"
#endif

int main(int argc, char** argv) {
  base::TestSuite test_suite(argc, argv);

#if defined(OS_MACOSX) && !defined(OS_IOS)
  base::MachPortBroker mach_broker("mojo_test");
  CHECK(mach_broker.Init());
  mojo::edk::SetMachPortProvider(&mach_broker);
#endif

  return base::LaunchUnitTests(
      argc, argv,
      base::Bind(&base::TestSuite::Run, base::Unretained(&test_suite)));
}
