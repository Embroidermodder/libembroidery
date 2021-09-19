static int read100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    unsigned char b[4];
    EmbStitch st;

    embPattern_loadExternalColorFile(pattern, fileName);
    while (embFile_read(b, 1, 4, file) == 4) {
        /* What does byte b[1] do? Is it the color index? */
        st.flags = NORMAL;
        st.x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2];
        st.y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3];
        /*if(!(b[0] & 0xFC)) st.flags = JUMP; TODO: review & fix */
        if (!(b[0] & 0x01))
            st.flags = STOP;
        if (b[0] == 0x1F)
            st.flags = END;
        st.color = 1;
        st.x /= 10.0;
        st.y /= 10.0;
        embPattern_addStitchRel(pattern, st.x, st.y, st.flags, st.color);
    }

    return 1;
}

static int write100(EmbPattern* pattern, EmbFile* file, const char* fileName)
{
    return 0; /*TODO: finish write100 */
}

