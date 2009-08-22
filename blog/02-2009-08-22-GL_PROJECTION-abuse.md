GL_PROJECTION abuse
===================

I am apparently guilty of [abusing the `GL_PROJECTION` matrix][abuse].


Background
----------

When starting the project I decided to spend as little energy on learning OpenGL as possible, making due with what I already knew. As it turns out, I had a lot I needed to learn anyway and during the course of this project I have learned:

 1. Not to use P-buffers (this was quick)
 2. To use [framebuffer objects][FBO]
 3. To use floating point textures for higher dynamic range
 4. Ways to bend `GL_BLEND` to do my bidding

When combining 2. and 3. in that list it turns out that there are some [strange, hard to debug, hidden requirements][RGBA16F].

I think the descision to make due with what I knew about OpenGL combined with the requirement to use floating point textures and framebuffer objects makes for a rather unfashionable combination of old OpenGL-code, which I learned at university and earlier, and recently out-dated extensions to OpenGL. In short, I think a lot of my OpenGL-code can make seasoned graphics developers cry.


What will I do?
---------------

I might actually take Steve Baker's advice on how to use the `GL_PROJECTION` matrix, because it really does make sense. However, I am not about to embark on a conversion to using only the appreciated (non-depreceated) subset of OpenGL 3.1 or anything of that magnitude. For the time being, the goal is to get the project [done][done].


[abuse]: http://www.sjbaker.org/steve/omniv/projection_abuse.html
[RGBA16F]: http://stackoverflow.com/questions/640095/when-using-a-glrgba16farb-texture-it-contains-just-crap-but-i-get-no-error-me
[FBO]: http://en.wikipedia.org/wiki/Framebuffer_Object
[done]: http://www.brepettis.com/blog/2009/3/3/the-cult-of-done-manifesto.html

