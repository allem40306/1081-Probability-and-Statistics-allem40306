from keras.models import Sequential
from keras.layers import Dense,Conv2D,Flatten,MaxPooling2D,Dropout
import keras.backend.tensorflow_backend as KTF
import tensorflow as tf
from service.analyticService.core.analyticCore.classificationBase import classification
from service.analyticService.core.analyticCore.utils import XYdataGenerator,XdataGenerator
from math import ceil

class r10525069_multiCNN(classification):
    def trainAlgo(self):
        hidden_kernel_size = (self.param['hidden_kernel_size'],self.param['hidden_kernel_size'])
        hidden_activation = self.param['hidden_activation']
        dropout_rate = self.param['dropout_rate']
        
        self.model=Sequential()

        self.model.add(Conv2D(8, hidden_kernel_size, activation=hidden_activation, input_shape=(32, 32, 3), data_format='channels_last'))
        self.model.add(Conv2D(8, hidden_kernel_size, activation=hidden_activation))
        self.model.add(MaxPooling2D((2, 2)))

        self.model.add(Flatten())
        self.model.add(Dense(16, activation=hidden_activation))
        self.model.add(Dropout(dropout_rate))
        self.model.add(Dense(self.outputData['Y'].shape[1], activation='softmax'))

        self.model.compile(loss='categorical_crossentropy',optimizer=self.param['optimizer'])
        self.model.fit_generator(
            XYdataGenerator(self.inputData['X'],self.outputData['Y'],32,32,self.param['batch_size']),
            steps_per_epoch=int(ceil((len(self.inputData['X'])/self.param['batch_size']))),
            epochs=self.param['epochs']
        )
    def predictAlgo(self):
        
        r=self.model.predict_generator(
            XdataGenerator(self.inputData['X'],32,32,self.param['batch_size']),
            steps=int(ceil((len(self.inputData['X'])/self.param['batch_size'])))
        )
        self.result['Y']=r
