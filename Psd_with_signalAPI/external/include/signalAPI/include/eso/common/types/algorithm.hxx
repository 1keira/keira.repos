/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef IPL_ALGORITHM_HXX
#define IPL_ALGORITHM_HXX
/****************************************************************************/

#include <common/ipl_namespace.hxx>
#include <algorithm>


namespace IPL_NAMESPACE {

    using std::for_each;
    using std::count;
    using std::count_if;
    using std::mismatch;

    using std::find;
    using std::find_if;

    using std::find_end;
    using std::find_first_of;
    using std::adjacent_find;

    using std::search;
    using std::search_n;

    using std::copy;
    //using std::copy_if;
    using std::copy_backward;
    using std::fill;
    using std::fill_n;
    using std::transform;
    using std::generate;
    using std::generate_n;

    using std::remove;
    using std::remove_if;
    using std::remove_copy;
    using std::remove_copy_if;

    using std::replace;
    using std::replace_if;
    using std::replace_copy;
    using std::replace_copy_if;

    using std::swap;
    using std::swap_ranges;
    using std::iter_swap;

    using std::reverse;
    using std::reverse_copy;
    using std::rotate_copy;
    using std::unique;
    using std::unique_copy;

    using std::partition;
    using std::stable_partition;

    using std::sort;
    using std::partial_sort;
    using std::partial_sort_copy;
    using std::stable_sort;

    using std::lower_bound;
    using std::upper_bound;
    using std::binary_search;
    using std::equal_range;

    using std::merge;
    using std::inplace_merge;
    using std::includes;
    using std::set_difference;
    using std::set_intersection;
    using std::set_symmetric_difference;
    using std::set_union;

    using std::make_heap;
    using std::push_heap;
    using std::pop_heap;
    using std::sort_heap;

    using std::max;
    using std::max_element;
    using std::min;
    using std::min_element;

    using std::equal;
    using std::lexicographical_compare;

    using std::next_permutation;
    using std::prev_permutation;
#if 0
    // deviate from the standard:
    using std::accumulate;
    using std::inner_product;
    using std::adjacent_difference;
    using std::partial_sum;

    using std::qsort;
    using std::bsearch;
#endif

}

/****************************************************************************/
#endif
/****************************************************************************/
