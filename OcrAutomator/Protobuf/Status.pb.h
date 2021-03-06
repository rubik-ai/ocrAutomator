// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Status.proto

#ifndef PROTOBUF_Status_2eproto__INCLUDED
#define PROTOBUF_Status_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace Docapost {
namespace IA {
namespace Tesseract {
namespace Proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Status_2eproto();
void protobuf_AssignDesc_Status_2eproto();
void protobuf_ShutdownFile_Status_2eproto();

class Status;

// ===================================================================

class Status : public ::google::protobuf::Message {
 public:
  Status();
  virtual ~Status();

  Status(const Status& from);

  inline Status& operator=(const Status& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Status& default_instance();

  void Swap(Status* other);

  // implements Message ----------------------------------------------

  Status* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Status& from);
  void MergeFrom(const Status& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 total = 1;
  inline bool has_total() const;
  inline void clear_total();
  static const int kTotalFieldNumber = 1;
  inline ::google::protobuf::int32 total() const;
  inline void set_total(::google::protobuf::int32 value);

  // required int32 skip = 2;
  inline bool has_skip() const;
  inline void clear_skip();
  static const int kSkipFieldNumber = 2;
  inline ::google::protobuf::int32 skip() const;
  inline void set_skip(::google::protobuf::int32 value);

  // required int32 done = 3;
  inline bool has_done() const;
  inline void clear_done();
  static const int kDoneFieldNumber = 3;
  inline ::google::protobuf::int32 done() const;
  inline void set_done(::google::protobuf::int32 value);

  // required int32 psm = 4;
  inline bool has_psm() const;
  inline void clear_psm();
  static const int kPsmFieldNumber = 4;
  inline ::google::protobuf::int32 psm() const;
  inline void set_psm(::google::protobuf::int32 value);

  // required int32 oem = 5;
  inline bool has_oem() const;
  inline void clear_oem();
  static const int kOemFieldNumber = 5;
  inline ::google::protobuf::int32 oem() const;
  inline void set_oem(::google::protobuf::int32 value);

  // required string lang = 6;
  inline bool has_lang() const;
  inline void clear_lang();
  static const int kLangFieldNumber = 6;
  inline const ::std::string& lang() const;
  inline void set_lang(const ::std::string& value);
  inline void set_lang(const char* value);
  inline void set_lang(const char* value, size_t size);
  inline ::std::string* mutable_lang();
  inline ::std::string* release_lang();
  inline void set_allocated_lang(::std::string* lang);

  // @@protoc_insertion_point(class_scope:Docapost.IA.Tesseract.Proto.Status)
 private:
  inline void set_has_total();
  inline void clear_has_total();
  inline void set_has_skip();
  inline void clear_has_skip();
  inline void set_has_done();
  inline void clear_has_done();
  inline void set_has_psm();
  inline void clear_has_psm();
  inline void set_has_oem();
  inline void clear_has_oem();
  inline void set_has_lang();
  inline void clear_has_lang();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 total_;
  ::google::protobuf::int32 skip_;
  ::google::protobuf::int32 done_;
  ::google::protobuf::int32 psm_;
  ::std::string* lang_;
  ::google::protobuf::int32 oem_;
  friend void  protobuf_AddDesc_Status_2eproto();
  friend void protobuf_AssignDesc_Status_2eproto();
  friend void protobuf_ShutdownFile_Status_2eproto();

  void InitAsDefaultInstance();
  static Status* default_instance_;
};
// ===================================================================


// ===================================================================

// Status

// required int32 total = 1;
inline bool Status::has_total() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Status::set_has_total() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Status::clear_has_total() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Status::clear_total() {
  total_ = 0;
  clear_has_total();
}
inline ::google::protobuf::int32 Status::total() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.total)
  return total_;
}
inline void Status::set_total(::google::protobuf::int32 value) {
  set_has_total();
  total_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.total)
}

// required int32 skip = 2;
inline bool Status::has_skip() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Status::set_has_skip() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Status::clear_has_skip() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Status::clear_skip() {
  skip_ = 0;
  clear_has_skip();
}
inline ::google::protobuf::int32 Status::skip() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.skip)
  return skip_;
}
inline void Status::set_skip(::google::protobuf::int32 value) {
  set_has_skip();
  skip_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.skip)
}

// required int32 done = 3;
inline bool Status::has_done() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Status::set_has_done() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Status::clear_has_done() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Status::clear_done() {
  done_ = 0;
  clear_has_done();
}
inline ::google::protobuf::int32 Status::done() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.done)
  return done_;
}
inline void Status::set_done(::google::protobuf::int32 value) {
  set_has_done();
  done_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.done)
}

// required int32 psm = 4;
inline bool Status::has_psm() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Status::set_has_psm() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Status::clear_has_psm() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Status::clear_psm() {
  psm_ = 0;
  clear_has_psm();
}
inline ::google::protobuf::int32 Status::psm() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.psm)
  return psm_;
}
inline void Status::set_psm(::google::protobuf::int32 value) {
  set_has_psm();
  psm_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.psm)
}

// required int32 oem = 5;
inline bool Status::has_oem() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void Status::set_has_oem() {
  _has_bits_[0] |= 0x00000010u;
}
inline void Status::clear_has_oem() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void Status::clear_oem() {
  oem_ = 0;
  clear_has_oem();
}
inline ::google::protobuf::int32 Status::oem() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.oem)
  return oem_;
}
inline void Status::set_oem(::google::protobuf::int32 value) {
  set_has_oem();
  oem_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.oem)
}

// required string lang = 6;
inline bool Status::has_lang() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void Status::set_has_lang() {
  _has_bits_[0] |= 0x00000020u;
}
inline void Status::clear_has_lang() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void Status::clear_lang() {
  if (lang_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    lang_->clear();
  }
  clear_has_lang();
}
inline const ::std::string& Status::lang() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Status.lang)
  return *lang_;
}
inline void Status::set_lang(const ::std::string& value) {
  set_has_lang();
  if (lang_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    lang_ = new ::std::string;
  }
  lang_->assign(value);
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Status.lang)
}
inline void Status::set_lang(const char* value) {
  set_has_lang();
  if (lang_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    lang_ = new ::std::string;
  }
  lang_->assign(value);
  // @@protoc_insertion_point(field_set_char:Docapost.IA.Tesseract.Proto.Status.lang)
}
inline void Status::set_lang(const char* value, size_t size) {
  set_has_lang();
  if (lang_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    lang_ = new ::std::string;
  }
  lang_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Docapost.IA.Tesseract.Proto.Status.lang)
}
inline ::std::string* Status::mutable_lang() {
  set_has_lang();
  if (lang_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    lang_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Docapost.IA.Tesseract.Proto.Status.lang)
  return lang_;
}
inline ::std::string* Status::release_lang() {
  clear_has_lang();
  if (lang_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = lang_;
    lang_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void Status::set_allocated_lang(::std::string* lang) {
  if (lang_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete lang_;
  }
  if (lang) {
    set_has_lang();
    lang_ = lang;
  } else {
    clear_has_lang();
    lang_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Docapost.IA.Tesseract.Proto.Status.lang)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Proto
}  // namespace Tesseract
}  // namespace IA
}  // namespace Docapost

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Status_2eproto__INCLUDED
