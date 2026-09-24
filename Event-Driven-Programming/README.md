# Event-Driven Programming

Event-driven programming is a paradigm where the flow of the program is determined by events — things that happen (user clicks, key presses, messages, timers, sensor signals). Instead of running top-to-bottom in a fixed sequence, the program waits and reacts when events occur.

# Core Concepts


- Event: 	       Something that happens (click, keypress, message arrival)
- Event Source:	   The thing that generates the event (button, socket, timer)
- Event Handler or  Listener: 	A function that runs when an event occurs
- Event Loop: 	The mechanism that waits for events and dispatches them to handlers
- Callback: 	A function passed to be called later

So besides just putting images on the screen, the games require that you handle input from the user. You can do that with SDL using the event handling system.
