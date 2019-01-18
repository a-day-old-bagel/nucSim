
# Set required version and policy version
cmake_minimum_required( VERSION 3.9.2 FATAL_ERROR )
cmake_policy( VERSION 3.9.2...3.13 )

project( pi_mc VERSION 0.01.01.01 LANGUAGES C )

add_executable( pi_mc
	pi_mc.c
	random_number.h
)

target_link_libraries( pi_mc
	m
)

