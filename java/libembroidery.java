/* Libembroidery 1.0 on Java
 *
 * Copyright 2022 The Embroidermodder Team
 * Licensed under the term of the zlib license.
 *
 * Due to potential crashing that can be caused by
 * actually wrapping C for Java this is a pure Java
 * program that calls the embroider command line
 * in such a way that memory can be buffered back and
 * forth via a file.
 *
 * This should be good enough to use the library for
 * Embroidermodder on Android, but it's worth including
 * here for any other application that may need to make
 * similar calls.
 */

package org.embroidermodder;

public class libembroidery {
    public static void main( String[] args ) {
        System.out.println( "Hello World!" );
    }
}
