const mysqlConnection = require('../database/db')
const util = require('util');
const query = util.promisify(mysqlConnection.query).bind(mysqlConnection);

// MQTT
const mqtt = require('mqtt')

/* PROTOCOLO MQTT - TCP Port: 1883 - Primera opción de conectarse al broker */
// const host = 'broker.emqx.io'
// const port = '1883'
// //const clientId = `mqtt_${Math.random().toString(16).slice(3)}`
// const clientId = 'mqttx_04be0b77_1'

// const connectUrl = `mqtt://${host}:${port}`


/* PROTOCOLO WS - WebSocket Port: 8083 - Segunda opción de conectarse al broker */
const protocol = 'ws'
const host = 'broker.emqx.io'
const port = '8083'
const path = '/mqtt'
//const clientId = 'mqttx_04be0b77_2'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`

const connectUrl = `${protocol}://${host}:${port}${path}`

/* Cliente de conexión al Broker MQTT */
const client = mqtt.connect(connectUrl, {
    clientId,
    clean: true,
    connectTimeout: 4000,
    username: '',
    password: '',
    reconnectPeriod: 4000,
})

/* Definir Topics - Por convención 'topic/<IDENTIFICADOR>' */
const TOPIC_TEMPERATURA = "topic/temperatura_G100"


/* ** ENDPOINT - Para Comparar HTTP vs MQTT - No es necesario para la implementación con MQTT ** */
const publicacionesMQTT = async (req, res) => {
    const body = req.body
    console.log("body", body)

    try {
        const resFechaHora = await query('SELECT NOW() as fechaFull;');

        const dataSensor = {
            topic: body.topic,
            valor: body.payload,
            fecha: resFechaHora[0].fechaFull
        }

        await query('INSERT INTO sensores SET ?', dataSensor)

        res.status(200).json({ message: `Topic Recibido - ${body.topic}` });
    } catch (error) {
        console.error("ERROR: publicacionesMQTT - ", error)

        res.status(500).json({
            status: "FAILED",
            message: "Error al enviar solicitud de amistad"
        })
    }
    
}


/* ** EVENTOS MQTT ** */

/* Suscribirse a un Topic */
const suscribirse = () => {
    client.subscribe([TOPIC_TEMPERATURA], () => {
        console.log(`Suscrito al topic '${TOPIC_TEMPERATURA}'`)
    })
}

/* Recibir los mensajes de los topics suscritos */
const mensajesMQTT = async (topic, payload) =>{
    console.log('Mensaje Recibido:', topic, payload.toString())

    try {
        const resFechaHora = await query('SELECT NOW() as fechaFull;');

        const dataSensor = {
            topic: topic,
            valor: payload.toString(),
            fecha: resFechaHora[0].fechaFull
        }

        await query('INSERT INTO sensores SET ?', dataSensor)

    } catch (error) {
        console.error("ERROR: mensajesMQTT - ", error)

    }
}


module.exports = {
    client,
    suscribirse,
    mensajesMQTT,
    publicacionesMQTT
}