## Ideas

#### Rendering system

There are two forms of render that will be produced.

1. A raster format as ppm so we can have a pixel for pixel output (for example extracting the embedded images in some formats).
2. The SVG format that will be fairly similar to InkStitch's format.

We have an EmbImage struct to store the raster format.

```
embroider test01.csv --render
```

currently creates a blank image. Previously the Hilbert curve test managed to
create a correctly rendered version.

#### Identify the meaning of these TODO items

* Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug #179 

#### Progress Chart

The chart of successful from-to conversions (previously a separate issue)
is something that should appear in the README.

#### Tactile art and braille support

One application I'd like to leave a reminder here for is automating embroidery
for blind and partially sighted people.

There are many limitations to making braille (cost, poor support, lack of
widespread adoption in the sighted world) and as such there is a strong DIY
culture around it.

There are blind internet users who can also run terminal applications using a
refreshable braille display, so in theory we could support an application like
this for them:

```
embroider --braille "Hello, world!" hello.dst
```

which would produce braille that would read "Hello, world!" as an embroidery
design.

Another option is tactile fills that use the same fill algorithms but are
designed better to facilitate tactile art.

I think the way forward on this is to call up the RNIB business advice line and
ask for assistance once we have a working model. That way they can get us in
contact with experts to review how legible the output is and usable the
software is for the intended audience.

This is less important than getting better machine support but given the high
social impact I think it should be a priority.
