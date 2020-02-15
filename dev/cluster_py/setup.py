from distutils.core import setup, Extension

module1 = Extension("QCLSolver.core", 
	sources=["./QCLSolver/core/cluster_expansion.c", "./QCLSolver/core/complex.c", "./QCLSolver/core/main_wrapper.c", "./QCLSolver/core/normalizer.c", "./QCLSolver/core/operator_tree.c", "./QCLSolver/core/position_tree.c", "./QCLSolver/core/solver.c", "./QCLSolver/core/static_dtree.c"], 
	include_dirs=['./QCLSolver/core/'])

setup(name="QCLSolver",
      version="1.0",
      description="A tool for cluster expansion solver.",
      packages=['QCLSolver'],
      ext_modules=[module1])