import mms
import unittest
from mooseutils import fuzzyEqual, fuzzyAbsoluteEqual

class TestAverage(unittest.TestCase):
    def test(self):
        df1 = mms.run_spatial('lid-driven.i', 8, y_pp=['L2u', 'L2v', 'L2p'], mpi=8)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=['L2u', 'L2v', 'L2p'], marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('average.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 0., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class TestRC(unittest.TestCase):
    def test(self):
        df1 = mms.run_spatial('rc.i', 8, y_pp=['L2u', 'L2v', 'L2p'], mpi=8)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=['L2u', 'L2v', 'L2p'], marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('rc.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

if __name__ == '__main__':
    unittest.main(__name__, verbosity=2)
