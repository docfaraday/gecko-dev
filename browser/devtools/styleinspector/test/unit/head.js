/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */
"use strict";

const Cc = Components.classes;
const Ci = Components.interfaces;
const Cu = Components.utils;
const Cr = Components.results;
const CC = Components.Constructor;

// We also need a valid nsIXulAppInfo
Cu.import("resource://testing-common/AppInfo.jsm");
updateAppInfo();

Cu.import("resource://gre/modules/devtools/Loader.jsm");
