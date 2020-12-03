import mms
import unittest
from mooseutils import fuzzyEqual, fuzzyAbsoluteEqual

class Test1DAverage(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2p']
        df1 = mms.run_spatial('1d-average.i', 7, y_pp=labels)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('1d-average.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 0., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class Test1DRC(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2p']
        df1 = mms.run_spatial('1d-rc.i', 11, y_pp=labels)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('1d-rc.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class Test2DRC(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2v', 'L2p']
        df1 = mms.run_spatial('2d-rc.i', 8, y_pp=labels, mpi=8)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('2d-rc.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            # This appears to be converging asymptotically to 1, however, it
            # takes too much CPU power for a test to go through enough mesh
            # refinements to get there
            if key == 'L2p':
                self.assertTrue(value >= .95)
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))


if __name__ == '__main__':
    unittest.main(__name__, verbosity=2)