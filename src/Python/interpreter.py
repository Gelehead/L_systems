import sys
import os

def visualize_turtle_graphics(grammar_path, angle=90, step_size=10):
    """
    Visualize the L-system using turtle graphics.
    
    Args:
        lsystem_result (str): The L-system string to visualize
        angle (int): The angle to turn in degrees
        step_size (int): The step size for forward movement
    """
    import turtle
    
    path = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), grammar_path))

    f = open(path)
    instructions = f.readline()
    #print(instructions[:100])
    f.close()
    
    # Set up the turtle
    t = turtle.Turtle()
    
    screen = turtle.Screen()
    screen.setup(width=1400, height=750, startx=100, starty=50)
    
    # go up left
    t.penup()
    t.goto((-600, 100))
    t.pendown()
    t.hideturtle()
    
    t.speed(0)  # Fastest speed
    turtle.tracer(0, 0)  # Turn off animation
    
    # Define the turtle graphics rules
    stack = []
    
    for char in instructions:
        if char == 'F':  # Move forward and draw
            t.forward(step_size)
        elif char == 'f':  # Move forward without drawing
            t.penup()
            t.forward(step_size)
            t.pendown()
        elif char == 'p' or char == '+':  # Turn right
            t.right(angle)
        elif char == 'm' or char == '-':  # Turn left
            t.left(angle)
        elif char == 'b' or char == '[':  # Save current state
            stack.append((t.position(), t.heading()))
        elif char == 'd' or char == ']':  # Restore saved state
            position, heading = stack.pop()
            t.penup()
            t.goto(position)
            t.setheading(heading)
            t.pendown()
    
    # Update the screen
    turtle.update()
    turtle.exitonclick()

visualize_turtle_graphics(sys.argv[3], float(sys.argv[2]), int(sys.argv[1]))