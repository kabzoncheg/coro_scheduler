int *merge_sort(int *nsrt, int *srt, unsigned int l_idx, unsigned int r_idx) {
    if (l_idx >= r_idx) {
        return nsrt;
    }

    unsigned int m_idx =  (l_idx +r_idx ) / 2;
    merge_sort(nsrt, srt, l_idx, m_idx);
    merge_sort(nsrt, srt, m_idx + 1, r_idx);

    unsigned int pointer_left = l_idx;       // pointer_left points to the beginning of the left sub-array
    unsigned int pointer_right = m_idx+ 1;        // pointer_right points to the beginning of the right sub-array

    for (unsigned int k = l_idx; k <= r_idx; k++) {
        if (pointer_left == m_idx + 1) {      // left pointer has reached the limit
            srt[k] = nsrt[pointer_right];
            pointer_right++;
        } else if (pointer_right == r_idx + 1) {        // right pointer has reached the limit
            srt[k] = nsrt[pointer_left];
            pointer_left++;
        } else if (nsrt[pointer_left] < nsrt[pointer_right]) {        // pointer left points to smaller element
            srt[k] = nsrt[pointer_left];
            pointer_left++;
        } else {        // pointer right points to smaller element
            srt[k] = nsrt[pointer_right];
            pointer_right++;
        }
    }
    for (unsigned int k = l_idx; k <= r_idx; k++) {      // copy the elements from aux[] to a[]
        nsrt[k] = srt[k];
    }
    return srt;
}