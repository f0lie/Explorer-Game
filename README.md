# Legend_of_the_Swamp
A UF group project that attempts to create a limited Legend of Zelda clone.

## Tools we will be using
[Slack](legendoftheswamp.slack.com)
  * This is so we can communicate. Group texting is pretty ghetto and someone's phone could be wiped.

[SFML](http://www.sfml-dev.org/documentation/2.3.2/)
  * This is so we can interact with the computer. Its also cross platform so you don't have to install Linux.

Git
  * This is so we can track changes and merge our code togethe.rC

Any IDE
  * With the proper setup, it shouldn't matter what IDE you are using or even what OS.

[Cmake](https://en.wikipedia.org/wiki/CMake)
  * Build generator system. You run it and it makes the correct build files for your system. It basically makes compiling not painful/impossible.

[Google Test](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)
 * It is extremely important to have tests to verify the project.

## Expectations
We should meet very often. Code with a very collabration based project and we need to communicate in person to effectively work.

The code will break very often and thats fine IF YOU **FIX** IT. Do not leave things broken.

When you submit your code to this main repo, I will review your code. I will mainly be follow standard practices of C++. For more specific examples go to the .pdf I linked below. No one will remember all of them and neither will I. Just keep write and slowly improve your code.

Please have some form of documentation with your code. Code without saying what it actually does is completely useless and dangerous code. Tests aka things to make sure its actually does what it says is nice.

Do one thing at time. If you are working on physics, focus on writing physics. If you need to display modules to work with, ask the dude that is working with display, pull his/her code and work from that.

The build system will be Cmake because ~~its what my ide came with~~ it is cross platform and works with all major IDEs including Visual Studio.

## Resources for the group
Hopefully these links will help you on the project.
#### What you need to do

##### Learn git
[Very good tutorial](https://www.atlassian.com/git/)

Git is a tool that allows us to track changes and combine the changes. The real value of git is with projects that demand the collaboration. The above link will pretty much have everything you need to know.

###### Workflow of git
Most of the time its going to be something like this:
  1. Fork the main repo on github *// you do this via github, you are basically have a local copy of this repo on your account.*
  2. git add. *// stages your changes*
  3. git commit -m "added more memes" *// write your changes to the branch*
  4. do the first two again until you are happy with your repo
  5. git pull upstream master *// upstream is the main repo that I control. You are making sure that you are up to date with the main repo.*
  6. deal with merge conflicts *// you pulled changes from the main remote that may progressed ahead of you. So it may conflict with your code. No problem, git helps you deal with them.*
  7. git push origin master *// origin is basically the url to a remote repo. You are uploading code to github*
  8. Make a pull request on github *// politely ask for me to take your changes and add them to the main repo. I will review your code and likely yell at you*

##### Watch this video
[linky-poo](https://www.youtube.com/watch?v=TC9zhufV_Z8)
It's a presentation at CppCon (a conference where the ~~nerdest~~ coolest people go to). The guy walks through using SFML to develop a simple game.

##### ~~Sacrifice your newborn~~ Read modern C++11/14 standards
If you want an example of modern C++ look at my repo magic_sqaure.

[C++ FAQ](https://isocpp.org/wiki/faq)

* This is a wonderful FAQ that touches on a lot of topics about C++.

[Bjarne Stroustrup on Writing Good Code](https://www.youtube.com/watch?v=1OEu9C51K2A)

* Some random Danish dude talks about coding good code.

[CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)

* This is a draft for common core practices that the entire C++ community should use. Very good and readable.

Effective C++ and Modern Effective C++

* These are two EXTREMELY good books on writing high quality C++. If you ask me, I can let you "borrow" my "physical" copy of the book.

[C++ Code Standard for things that go vroom vroom](http://stroustrup.com/JSF-AV-rules.pdf)

* The random Danish dude writes some guidelines on writing good C++. It actually explains why you do certain things. Use this as a jumping point to research more points about C++.

##### Learn SFML and look at other games.
This is honestly not the most important thing. SFML is stands for Simple Fast Multimedia Library. It is a way to interact with your keyboard, audio, and display things. While signifact, it WILL NOT guide the design of our game.

There are other examples of open source Legend of Zelda games. You should take a peek at them and see what they do.

[Tutorial on what we are trying to do](https://github.com/SFML/SFML/wiki/Tutorial:-Basic-Game-Engine)

##### Use reddit
[/r/gamedev](www.reddit.com/r/gamedev)

[/r/learnprogramming](www.reddit.com/r/learnprogramming)

These two sub-reddits are very good for learning things. Use the search bar with the terms "C++" or "game" and you will find a lot of handy things.
