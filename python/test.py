#!/usr/bin/env python3

r"""
Part of libembroidery

Copyright 2022 The Embroidermodder Team
Licensed under the terms of the zlib licence.

The test suite for the libembroidery Python bindings.

Similar to, although not a replica of, the internal
tests. This cannot replace them because some systems
that will run the library won't support Python.

(Libembroidery may need to include some truly
ancient PC in order to deal with the older
embroidery machines that they may talk to.)
"""

import math
import unittest
import libembroidery as emb

class TestLibembroidery(unittest.TestCase):
    r"""
    The parent class for all of the bindings
    tests, this could be made to chain into the
    internal C testing.
    """
    def test_vector_length(self):
        " Tests the vector length function. "
        v = emb.vector(3.0, 4.0)
        self.assertAlmostEqual(v.length(), 5.0)

    def test_arc(self):
        " . "
        arc = emb.arc(1.0, 2.0, 2.0, 3.0, 4.0, 6.0)
        self.assertAlmostEqual(5.0, 5.0)

    def test_circle(self):
        " . "
        circle = emb.circle(3.0, 4.0, 2.0)
        self.assertAlmostEqual(5.0, 5.0)

    def test_ellipse(self):
        " . "
        ellipse = emb.ellipse(3.0, 4.0, 7.0, 4.0)
        self.assertAlmostEqual(5.0, 5.0)

    def test_path(self):
        " . "
        path = emb.path()
        path.x = 3.0
        path.y = 4.0
        self.assertAlmostEqual(5.0, 5.0)

    def test_main(level):
        #svg1Result = convert("test01.csv", "test01.svg")
        #svg2Result = convert("test02.csv", "test02.svg")
        #svg3Result = convert("test03.csv", "test03.svg")
        #dst1Result = convert("test01.csv", "test01.dst")
        #dst2Result = convert("test02.csv", "test02.dst")
        #dst3Result = convert("test03.csv", "test03.dst")
        pattern = emb.pattern_create()
        image = emb.embImage_create(100, 100)
        hilbertCurveResult = emb.hilbert_curve(pattern, 3)
        renderResult = emb.embImage_render(pattern, 20.0, 20.0, "hilbert_level_3.ppm")
        simulateResult = emb.embImage_simulate(pattern, 20.0, 20.0, "hilbert_level_3.avi")
        emb.image_free(image)
        emb.pattern_free(pattern)

    def test_circle_tangent(self):
        # Declare memory without allocating.
        t0 = emb.EmbCircle()
        t1 = emb.EmbCircle()
        # Problem definition
        c = emb.circle(0.0, 0.0, 3.0)
        p = emb.vector(4.0, 0.0)
        # Test
        emb.getCircleTangentPoints(c, p, t0, t1)
        self.assertAlmostEqual(t0.x, 2.2500)
        self.assertAlmostEqual(t0.y, 1.9843)
        self.assertAlmostEqual(t1.x, 2.2500)
        self.assertAlmostEqual(t1.y, -1.9843)

    def test_circle_tangent_2(self):
        # Declare memory without allocating.
        t0 = emb.EmbVector()
        t1 = emb.EmbVector()
        # Problem definition
        c = emb.circle(20.1762, 10.7170, 6.8221)
        p = emb.vector(24.3411, 18.2980)
        # Test
        emb.getCircleTangentPoints(c, p, t0, t1)
        self.assertAlmostEqual(t0.x, 19.0911)
        self.assertAlmostEqual(t0.y, 17.4522)
        self.assertAlmostEqual(t1.x, 26.4428)
        self.assertAlmostEqual(t1.y, 13.4133)

    def test_thread_color(self):
        """
        TODO: Add capability for converting multiple files of various
        types to a single format. 

        Currently, we only convert a single file to multiple formats.
        """
        tColor = 0xFFD25F00
        c = emb.EmbColor(0xD2, 0x5F, 0x00)
        tBrand = emb.Sulky_Rayon
        tNum = emb.threadColorNum(c, tBrand)
        tName = ""
        emb.threadColorName(tName, c, tBrand)

        # Solution: tNum = 1833
        # Solution: Pumpkin Pie
        print("""
Color : 0x%X
Brand : %d
Num   : %d
Name  : %s

""" % (tColor, tBrand, tNum, tName))
        return 0

    def test_format_table(self):
        " . "
        tName = "example.zsk"
        f_format = emb.identify_format(tName)
        table = emb.formatTable[f_format]

        self.assertEqual(table.extension, ".zsk")
        self.assertEqual(table.description, "ZSK USA Embroidery  f_format")
        self.assertEqual(table.reader_state, 'U')
        self.assertEqual(table.writer_state, ' ')
        self.assertEqual(table.type, 1)

    def test_create_test_file_1(self):
        """
        """
        outf = "test1.csv"
        p = emb.pattern_create()
        self.assertNotEqual(p, 0)

        # 10mm circle
        for i in range(20):
            emb.pattern_addStitchRel(p, 0.0, 1.0, emb.JUMP, 0)

        for i in range(200):
            st = emb.EmbStitch()
            st.x = 10 + 10 * math.sin(i * 0.01 * math.pi)
            st.y = 10 + 10 * math.cos(i * 0.01 * math.pi)
            st.flags = emb.NORMAL
            st.color = 0
            emb.pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color)

        emb.pattern_addThread(p, emb.black_thread)
        emb.pattern_end(p)

        self.assertEqual(emb.pattern_writeAuto(p, outf), 1)

        emb.pattern_free(p)

    def test_create_test_file_2(self):
        """
        """
        outf = "test2.csv"
        p = emb.pattern_create()
        self.assertNotEqual(p, 0)

        # sin wave
        for i in range(100):
            st = emb.EmbStitch()
            st.x = 10 + 10 * math.sin(i * (0.5 / math.pi))
            st.y = 10 + i * 0.1
            st.flags = emb.NORMAL
            st.color = 0
            emb.pattern_addStitchAbs(p, st.x, st.y, st.flags, st.color)

        emb.pattern_add_thread(p, emb.black_thread)
        emb.pattern_end(p)

        self.assertEqual(emb.pattern_writeAuto(p, outf), 1)
        emb.pattern_free(p)

    def test_create_test_file_3(self):
        """
        """
        outf = "test3.csv"
        p = emb.pattern_create()
        self.assertNotEqual(p, 0)

        emb.pattern_addCircleObjectAbs(p, 10.0, 1.0, 5.0)

        emb.pattern_addThread(p, emb.black_thread)
        emb.pattern_convertGeometry(p)
        emb.pattern_end(p)

        self.assertEqual(emb.pattern_writeAuto(p, outf), 1)
        emb.pattern_free(p)

    def test_full_matrix(self):
        r"""
        Table of from/to for formats. What conversions after a
        from A to B conversion leave a file with the same render?

        Add command "--full-test-suite" for this full matrix.
        """
        f = open("full_matrix.txt", "wb")
        self.assertNotEqual(f, 0)
        nformats = emb.numberOfFormats

        success = 0
        ntests = (nformats - 1)*(nformats - 5)
        for i in range(nformats):
            table = emb.formatTable
            if table.color_only:
                continue

            fname = "test01%s" % table.extension
            self.create_test_file_1(fname)
            for j in range(nformats):
                pattern = emb.EmbPattern()
                fname_converted = ("test01_%s_converted_to%s" % 
                    (table[i].extension+1, table[j].extension))
                fname_image = ("test01_%s_converted_to%s.ppm" %
                    (table[i].extension+1, table[j].extension+1))
                print("Attempting: %s %s\n" % (fname, fname_converted))
                result = emb.convert(fname, fname_converted)
                emb.pattern_read(pattern, fname_converted, j)
                emb.image_render(pattern, 20.0, 20.0, fname_image)
                emb.pattern_free(pattern)
                f.write(f, "%d %d %f%% " % (i, j, 100*success/(1.0*ntests)))
                if not result:
                    f.write(f, "PASS\n")
                    success += 1
                else:
                    f.write(f, "FAIL\n")

        f.close()
        return 0

if __name__ == '__main__':
    unittest.main()

