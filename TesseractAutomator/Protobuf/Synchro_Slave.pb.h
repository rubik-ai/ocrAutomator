// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Synchro_Slave.proto

#ifndef PROTOBUF_Synchro_5fSlave_2eproto__INCLUDED
#define PROTOBUF_Synchro_5fSlave_2eproto__INCLUDED

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
#include "Result.pb.h"
// @@protoc_insertion_point(includes)

namespace Docapost {
namespace IA {
namespace Tesseract {
namespace Proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Synchro_5fSlave_2eproto();
void protobuf_AssignDesc_Synchro_5fSlave_2eproto();
void protobuf_ShutdownFile_Synchro_5fSlave_2eproto();

class Synchro_Slave;

// ===================================================================

class Synchro_Slave : public ::google::protobuf::Message {
 public:
  Synchro_Slave();
  virtual ~Synchro_Slave();

  Synchro_Slave(const Synchro_Slave& from);

  inline Synchro_Slave& operator=(const Synchro_Slave& from) {
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
  static const Synchro_Slave& default_instance();

  void Swap(Synchro_Slave* other);

  // implements Message ----------------------------------------------

  Synchro_Slave* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Synchro_Slave& from);
  void MergeFrom(const Synchro_Slave& from);
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

  // required int32 ThreadRunning = 1;
  inline bool has_threadrunning() const;
  inline void clear_threadrunning();
  static const int kThreadRunningFieldNumber = 1;
  inline ::google::protobuf::int32 threadrunning() const;
  inline void set_threadrunning(::google::protobuf::int32 value);

  // optional int32 NbFilesRequired = 2;
  inline bool has_nbfilesrequired() const;
  inline void clear_nbfilesrequired();
  static const int kNbFilesRequiredFieldNumber = 2;
  inline ::google::protobuf::int32 nbfilesrequired() const;
  inline void set_nbfilesrequired(::google::protobuf::int32 value);

  // repeated .Docapost.IA.Tesseract.Proto.Result Data = 3;
  inline int data_size() const;
  inline void clear_data();
  static const int kDataFieldNumber = 3;
  inline const ::Docapost::IA::Tesseract::Proto::Result& data(int index) const;
  inline ::Docapost::IA::Tesseract::Proto::Result* mutable_data(int index);
  inline ::Docapost::IA::Tesseract::Proto::Result* add_data();
  inline const ::google::protobuf::RepeatedPtrField< ::Docapost::IA::Tesseract::Proto::Result >&
      data() const;
  inline ::google::protobuf::RepeatedPtrField< ::Docapost::IA::Tesseract::Proto::Result >*
      mutable_data();

  // @@protoc_insertion_point(class_scope:Docapost.IA.Tesseract.Proto.Synchro_Slave)
 private:
  inline void set_has_threadrunning();
  inline void clear_has_threadrunning();
  inline void set_has_nbfilesrequired();
  inline void clear_has_nbfilesrequired();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 threadrunning_;
  ::google::protobuf::int32 nbfilesrequired_;
  ::google::protobuf::RepeatedPtrField< ::Docapost::IA::Tesseract::Proto::Result > data_;
  friend void  protobuf_AddDesc_Synchro_5fSlave_2eproto();
  friend void protobuf_AssignDesc_Synchro_5fSlave_2eproto();
  friend void protobuf_ShutdownFile_Synchro_5fSlave_2eproto();

  void InitAsDefaultInstance();
  static Synchro_Slave* default_instance_;
};
// ===================================================================


// ===================================================================

// Synchro_Slave

// required int32 ThreadRunning = 1;
inline bool Synchro_Slave::has_threadrunning() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Synchro_Slave::set_has_threadrunning() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Synchro_Slave::clear_has_threadrunning() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Synchro_Slave::clear_threadrunning() {
  threadrunning_ = 0;
  clear_has_threadrunning();
}
inline ::google::protobuf::int32 Synchro_Slave::threadrunning() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Synchro_Slave.ThreadRunning)
  return threadrunning_;
}
inline void Synchro_Slave::set_threadrunning(::google::protobuf::int32 value) {
  set_has_threadrunning();
  threadrunning_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Synchro_Slave.ThreadRunning)
}

// optional int32 NbFilesRequired = 2;
inline bool Synchro_Slave::has_nbfilesrequired() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Synchro_Slave::set_has_nbfilesrequired() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Synchro_Slave::clear_has_nbfilesrequired() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Synchro_Slave::clear_nbfilesrequired() {
  nbfilesrequired_ = 0;
  clear_has_nbfilesrequired();
}
inline ::google::protobuf::int32 Synchro_Slave::nbfilesrequired() const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Synchro_Slave.NbFilesRequired)
  return nbfilesrequired_;
}
inline void Synchro_Slave::set_nbfilesrequired(::google::protobuf::int32 value) {
  set_has_nbfilesrequired();
  nbfilesrequired_ = value;
  // @@protoc_insertion_point(field_set:Docapost.IA.Tesseract.Proto.Synchro_Slave.NbFilesRequired)
}

// repeated .Docapost.IA.Tesseract.Proto.Result Data = 3;
inline int Synchro_Slave::data_size() const {
  return data_.size();
}
inline void Synchro_Slave::clear_data() {
  data_.Clear();
}
inline const ::Docapost::IA::Tesseract::Proto::Result& Synchro_Slave::data(int index) const {
  // @@protoc_insertion_point(field_get:Docapost.IA.Tesseract.Proto.Synchro_Slave.Data)
  return data_.Get(index);
}
inline ::Docapost::IA::Tesseract::Proto::Result* Synchro_Slave::mutable_data(int index) {
  // @@protoc_insertion_point(field_mutable:Docapost.IA.Tesseract.Proto.Synchro_Slave.Data)
  return data_.Mutable(index);
}
inline ::Docapost::IA::Tesseract::Proto::Result* Synchro_Slave::add_data() {
  // @@protoc_insertion_point(field_add:Docapost.IA.Tesseract.Proto.Synchro_Slave.Data)
  return data_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Docapost::IA::Tesseract::Proto::Result >&
Synchro_Slave::data() const {
  // @@protoc_insertion_point(field_list:Docapost.IA.Tesseract.Proto.Synchro_Slave.Data)
  return data_;
}
inline ::google::protobuf::RepeatedPtrField< ::Docapost::IA::Tesseract::Proto::Result >*
Synchro_Slave::mutable_data() {
  // @@protoc_insertion_point(field_mutable_list:Docapost.IA.Tesseract.Proto.Synchro_Slave.Data)
  return &data_;
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

#endif  // PROTOBUF_Synchro_5fSlave_2eproto__INCLUDED