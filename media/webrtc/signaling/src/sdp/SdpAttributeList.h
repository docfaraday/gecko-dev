/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef _SDPATTRIBUTELIST_H_
#define _SDPATTRIBUTELIST_H_

#include "mozilla/UniquePtr.h"
#include "mozilla/Attributes.h"

#include "signaling/src/sdp/SdpEnum.h"
#include "signaling/src/sdp/SdpAttribute.h"

namespace mozilla {

class SdpAttributeList
{
public:
  typedef SdpAttribute::AttributeType AttributeType;

  virtual unsigned int CountAttributes(AttributeType type) const = 0;
  virtual bool HasAttribute(AttributeType type) const = 0;
  virtual const SdpAttribute& GetAttribute(AttributeType type, size_t index = 0) const = 0;

  virtual const SdpCandidateAttribute& GetCandidate() const = 0;
  virtual const SdpConnectionAttribute& GetConnection() const = 0;
  virtual const SdpExtmapAttribute& GetExtmap() const = 0;
  virtual const SdpFingerprintAttribute& GetFingerprint() const = 0;
  virtual const SdpFmtpAttribute& GetFmtp() const = 0;
  virtual const SdpGroupAttribute& GetGroup() const = 0;
  virtual const SdpIceOptionsAttribute& GetIceOptions() const = 0;
  virtual const std::string& GetIcePwd() const = 0;
  virtual const std::string& GetIceUfrag() const = 0;
  virtual const SdpIdentityAttribute& GetIdentity() const = 0;
  virtual const SdpImageattrAttribute& GetImageattr() const = 0;
  virtual std::string GetLabel() const = 0;
  virtual uint32_t GetMaxprate() const = 0;
  virtual uint32_t GetMaxptime() const = 0;
  virtual std::string GetMid() const = 0;
  virtual const SdpMsidAttribute& GetMsid() const = 0;
  virtual uint32_t GetPtime() const = 0;
  virtual const SdpRtcpAttribute& GetRtcp() const = 0;
  virtual const SdpRtcpFbAttribute& GetRtcpFb() const = 0;
  virtual const SdpRemoteCandidatesAttribute& GetRemoteCandidates() const = 0;
  virtual const SdpRtpmapAttribute& GetRtpmap() const = 0;
  virtual const SdpSctpmapAttribute& GetSctpmap() const = 0;
  virtual const SdpSetupAttribute& GetSetup() const = 0;
  virtual const SdpSsrcAttribute& GetSsrc() const = 0;
  virtual const SdpSsrcGroupAttribute& GetSsrcGroup() const = 0;

  virtual void SetAttribute(const SdpAttribute &) = 0;
};

}

#endif
