// Serial Port - Arduino
const {SerialPort} = require('serialport');
const {DelimiterParser} = require('@serialport/parser-delimiter')

const portSerial = new SerialPort({
    path: 'COM3',
    baudRate: 9600
})

const parserSerial = portSerial.pipe(new DelimiterParser({delimiter: '\n'}))

// Abrir conexion con Arduino a traves del puerto Serial
parserSerial.on('open', function(){
    console.log('Opened Serial Port.');
})


// Datos obtenidos desde Arduino a traves del puerto Serial
parserSerial.on('data', function (data) {
    
    const datoSensor = data.toString();
    console.log("datoSensor", datoSensor);

    // EXTRA: Generar Accion en Arduino cuando el dato recibido sea el valor de un Sensor
    if(typeof Number(data) === 'number' && !isNaN(Number(data))){
        const randomNumber = Math.floor(Math.random() * 2); // Número entre 0 y 1
        console.log("randomNumber:", randomNumber);
        portSerial.write(randomNumber.toString());
    }
    
});

module.exports = { portSerial, parserSerial };