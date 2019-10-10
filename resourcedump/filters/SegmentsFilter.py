#######################################################
#
# SegmentsFilter.py
# Python implementation of the Class SegmentsFilter
# Original author: romany
#
#######################################################


class SegmentsFilter:
    """this class is responsible for filtering the segments.
    """
    @staticmethod
    def get_segments(segments_lst, seg_type):
        """this method responsible for filtering the segments
           by returning only the relevant segments according
           the given type.
        """
        filter_func = (lambda x: x.get_type() == seg_type)
        filtered = filter(filter_func, segments_lst)
        return [el for el in filtered]
