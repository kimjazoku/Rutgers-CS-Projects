import numpy as np
import sympy as sp

#DEFINE TOLERANCE AND MAX ITERATION
tol = 1e-6
max_iter = 100

def method_tester():
    x = sp.symbols('x')

    functions = [ 
    ("f(x) = 1 - 2*x*exp(-x/2)", 1 - 2*x*sp.exp(-x/2), 0),
    ("f(x) = 5 - 1/x", 5 - 1/x, 1/4),
    ("f(x) = x**3 - 2*x - 5", x**3 - 2*x - 5, 2),
    ("f(x) = exp(x) - 2", sp.exp(x) - 2, 1),
    ("f(x) = x - exp(-x)", x - sp.exp(-x), 1),
    ("f(x) = x**6 - x - 1", x**6 - x - 1, 1),
    ("f(x) = x**2 - sin(x)", x**2 - sp.sin(x), 1/2),
    ("f(x) = x**3 - 2", x**3 - 2, 1),
    ("f(x) = x + tan(x)", x + sp.tan(x), 3),
    ("f(x) = 2 - (1/x)*ln(x)", 2 - (1/x)*sp.log(x), 1/3),
    ]

    for functionName, f_expr, x0 in functions:
        f = sp.lambdify(x, f_expr, 'numpy') #tells SymPy to convert symbolic expressions into functions that can be evaluated numerically
        f_prime = sp.lambdify(x, sp.diff(f_expr, x), 'numpy')

        #newton's method
        print()
        print(f"Testing {functionName} with initial guess {x0}")
        root_newton, iter_newton = newton_raphson(f, f_prime, x0, tol, max_iter)
        print(f"\tNewton's Method: Root = {root_newton}, Iterations = {iter_newton}")

        #secant method
       # print(f"Testing {functionName} with initial guesses {x0} and {x0+1}")
        print()
        root_secant, iter_secant = secant_method(f, x0, x0+1, tol, max_iter)
        print(f"\tSecant Method: Root = {root_secant}, Iterations = {iter_secant}")

        #bisection method
        #print(f"Testing {functionName} with initial guesses {x0} and {x0+1}")
        print()
        root_bisection, iter_bisection = bisection_method(f, x0, x0+1, tol, max_iter)
        print(f"\tBisection Method: Root = {root_bisection}, Iterations = {iter_bisection}")
def newton_raphson(f, f_prime, x0, tol, max_iter):
    x = x0 #grab the initial guess
    for i in range(max_iter):
        fx = f(x) #define the function
        if abs(fx) < tol: #if the function value is close enough to zero, return the root and the number of iterations
            return x, i
        fpx = f_prime(x) #define the derivative of the function
        if fpx == 0: #cannot continue, derivative is zero
            raise ValueError("The derivative is zero. Division by zero error.")
        x = x - fx / fpx #newton method
    raise ValueError("Max iterations reached without convergence.")

def secant_method(f, x0, x1, tol, max_iter):
    for i in range(max_iter):
        try:
            f_x0 = f(x0) #define the function at x0
            f_x1 = f(x1) #define the function at x1
            if abs(f_x1) < tol: #if the function value at x1 is close enough to zero, return the root and the number of iterations
                return x1, i
            if(f_x1 - f_x0 == 0):
                return x1, i
            x_new = x1 - f_x1 * ((x1 - x0) / (f_x1 - f_x0)) #calculate the new approximation
            x0 = x1 #update x0 and x1 for the next iteration
            x1 = x_new #update x1 for the next iteration
        except ZeroDivisionError as e: #if division by zero occurs, return the root and the number of iterations
            print(f"Error: {e}")
    raise ValueError("Max iterations reached without convergence.")

def bisection_method(f, a, b, tol, max_iter):

        # bisection_method(f, a, b, tol, max_iter)  # Recursively call the function with updated interval
        # This is how bisection method works
        # We are trying to find the root of the function (what number 'x' that makes the function = 0 or close to 0)
        # We take a value (in this case a) and make that our initial guess
        # We then calculate the midpoint (m) of our interval (a, b)
        # We then check if f(m) is less than or equal to tolerance level (tol)
            # If it is, we've found our root and return it along with the number of iterations
        # If it's not, we narrow down our interval to either the left or the right subinterval based on whether f(a) * f(m) < 0 or f(m) * f(b) < 0 respectively
        # We continue this process until we either find our root or reach the maximum number of iterations allowed
        # If we reach the maximum number of iterations without finding our root, we raise an error
        # This is the basic structure of the bisection method, and it's one of the simplest and most efficient methods to find roots of a function.
    #check to see if a and b have opposite signs
    if(f(a) * f(b) >= 0):
        print('a and b do not have opposite signs. Switching signs and trying again.')
        return
              
    for i in range(max_iter):
        if(f(a) * f(b) >= 0):
            print('a and b do not have opposite signs. Switching signs and trying again.')
            return
        # Calculate midpoint
        m = (a + b) / 2
        f_m = f(m)
        # Check if f(m) is close enough to zero (root found)
        if f(m) == 0:
            return m, i
        # Narrow down the interval
        elif f(a) * f(m) < 0: #if it is a negative value root exists from (a, m)
            #assign b to m 
            b = m  # Root is in the left subinterval
        elif f(b) * f(m) < 0: #if it is a positive value replace interval b
            a = m  # Root is in the right subinterval
        else:
            print()
            raise ValueError("Bisection method failed. No root found.")
    
    raise ValueError("Max iterations reached without convergence.")

method_tester()