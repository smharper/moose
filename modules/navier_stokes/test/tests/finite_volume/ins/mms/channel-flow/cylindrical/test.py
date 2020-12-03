import mms
import unittest
from mooseutils import fuzzyEqual, fuzzyAbsoluteEqual

class Test2DAverage(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2v', 'L2p']
        df1 = mms.run_spatial('2d-average.i', 6, y_pp=labels)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('2d-average.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class Test2DRC(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2v', 'L2p']
        df1 = mms.run_spatial('2d-rc.i', 9, y_pp=labels, mpi=16)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('2d-rc.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class Test2DAverageTemp(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2v', 'L2p', 'L2t']
        df1 = mms.run_spatial('2d-average-with-temp.i', 6, y_pp=labels)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('2d-average-with-temp.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            if key == 'L2p':
                self.assertTrue(fuzzyAbsoluteEqual(value, 1., .05))
            else:
                self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

class Test2DRCTemp(unittest.TestCase):
    def test(self):
        labels = ['L2u', 'L2v', 'L2p', 'L2t']
        df1 = mms.run_spatial('2d-average-with-temp.i', 9, "velocity_interp_method='rc'", y_pp=labels, mpi=16)

        fig = mms.ConvergencePlot(xlabel='Element Size ($h$)', ylabel='$L_2$ Error')
        fig.plot(df1, label=labels, marker='o', markersize=8, num_fitted_points=3, slope_precision=1)
        fig.save('2d-rc-with-temp.png')
        for key,value in fig.label_to_slope.items():
            print("%s, %f" % (key, value))
            self.assertTrue(fuzzyAbsoluteEqual(value, 2., .05))

if __name__ == '__main__':
    unittest.main(__name__, verbosity=2)