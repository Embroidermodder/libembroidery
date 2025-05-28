
function(t NAME)
    add_test(test_${NAME} test_${NAME})
endfunction(t)

t(arc)
t(circle_tangent)
t(convert)
t(fractal_generation)
t(thread_color)
