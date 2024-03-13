/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <common/ipl_namespace.hxx>
#include <iterator>

namespace IPL_NAMESPACE {

   using std::iterator;
   using std::iterator_traits;
   using std::input_iterator_tag;
   using std::output_iterator_tag;
   using std::forward_iterator_tag;
   using std::bidirectional_iterator_tag;
   using std::random_access_iterator_tag;

   using std::reverse_iterator;
   using std::back_insert_iterator;
   using std::front_insert_iterator;
   using std::insert_iterator;

   using std::istream_iterator;
   using std::ostream_iterator;
   using std::istreambuf_iterator;
   using std::ostreambuf_iterator;

   using std::front_inserter;
   using std::back_inserter;
   using std::inserter;

   using std::advance;
   using std::distance;
   using std::next;
   using std::prev;
   using std::begin;
   using std::end;


}