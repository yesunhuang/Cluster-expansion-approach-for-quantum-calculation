from distutils.core import setup, Extension

module1 = Extension("cluster", 
	sources=["cluster_expansion.c", "complex.c", "main_wrapper.c", "normalizer.c", "operator_tree.c", "position_tree.c", "solver.c", "static_dtree.c"], 
	include_dirs=['./'])

setup(name="cluster", 
	version="1.0", 
	description="A tool for cluster expansion solver.",
	ext_modules=[module1])