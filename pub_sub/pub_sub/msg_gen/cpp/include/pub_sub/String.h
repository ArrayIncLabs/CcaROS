/* Auto-generated by genmsg_cpp for file /home/cr-lab-tu/pub_sub/pub_sub/msg/String.msg */
#ifndef PUB_SUB_MESSAGE_STRING_H
#define PUB_SUB_MESSAGE_STRING_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace pub_sub
{
template <class ContainerAllocator>
struct String_ {
  typedef String_<ContainerAllocator> Type;

  String_()
  : data()
  {
  }

  String_(const ContainerAllocator& _alloc)
  : data(_alloc)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _data_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  data;


  typedef boost::shared_ptr< ::pub_sub::String_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pub_sub::String_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct String
typedef  ::pub_sub::String_<std::allocator<void> > String;

typedef boost::shared_ptr< ::pub_sub::String> StringPtr;
typedef boost::shared_ptr< ::pub_sub::String const> StringConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::pub_sub::String_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::pub_sub::String_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace pub_sub

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::pub_sub::String_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::pub_sub::String_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::pub_sub::String_<ContainerAllocator> > {
  static const char* value() 
  {
    return "992ce8a1687cec8c8bd883ec73ca41d1";
  }

  static const char* value(const  ::pub_sub::String_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x992ce8a1687cec8cULL;
  static const uint64_t static_value2 = 0x8bd883ec73ca41d1ULL;
};

template<class ContainerAllocator>
struct DataType< ::pub_sub::String_<ContainerAllocator> > {
  static const char* value() 
  {
    return "pub_sub/String";
  }

  static const char* value(const  ::pub_sub::String_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::pub_sub::String_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string data\n\
\n\
";
  }

  static const char* value(const  ::pub_sub::String_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::pub_sub::String_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.data);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct String_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pub_sub::String_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::pub_sub::String_<ContainerAllocator> & v) 
  {
    s << indent << "data: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.data);
  }
};


} // namespace message_operations
} // namespace ros

#endif // PUB_SUB_MESSAGE_STRING_H

