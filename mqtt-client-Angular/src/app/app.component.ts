import { Component } from '@angular/core';
import {
  IMqttMessage,
  IMqttServiceOptions,
  MqttService,
  IPublishOptions,
} from 'ngx-mqtt';
import { IClientSubscribeOptions } from 'mqtt-browser';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'],
})
export class AppComponent {

  constructor(private _mqttService: MqttService) {
    this.client = this._mqttService;
  }

  private curSubscription: Subscription | undefined;

  connection = {
    // Broker
    hostname: 'broker.emqx.io',
    port: 8083,
    path: '/mqtt',
    clean: true,
    connectTimeout: 4000,
    //reconnectPeriod: 1000*60*60,  // 1 hora
    reconnectPeriod: 4000, 
    // Credenciales de conexion
    clientId: 'mqttx_04be0b77_',
    username: '',
    password: '',
    protocol: 'ws',
  }

  TOPIC_TEMPERATURA = "topic/temperatura_G100";
  TOPIC_MOTOR = "topic/motor_G100";

  subscription = {
    topic: this.TOPIC_TEMPERATURA,
    qos: 0,
  };

  publish = {
    topic: this.TOPIC_MOTOR,
    qos: 0,
    payload: '',
  };

  client: MqttService | undefined;
  isConnection = false;
  subscribeSuccess = false;

  sensorTemperatura = 0;

  // Crear Conexion con el Broker 
  createConnection() {
    
    try {
      this.client?.connect(this.connection as IMqttServiceOptions)
    } catch (error) {
      console.log('mqtt.connect error', error);
    }

    this.client?.onConnect.subscribe(() => {
      this.isConnection = true
      console.log('¡La conexión se realizó correctamente!');
    });

    this.client?.onError.subscribe((error: any) => {
      this.isConnection = false
      console.log('La conexión falló', error);
    });

    this.client?.onMessage.subscribe((packet: any) => {
      console.log(`Mensaje recibido ${packet.payload.toString()} del topic ${packet.topic}`)

      if (packet.topic == this.TOPIC_TEMPERATURA){
        this.sensorTemperatura = packet.payload.toString()
      }
    })
  }

  // Suscribirse a un Topic
  doSubscribe() {
    const { topic, qos } = this.subscription
    console.log("this.subscription", this.subscription)

    this.curSubscription = this.client?.observe(topic, { qos } as IClientSubscribeOptions).subscribe((message: IMqttMessage) => {
      this.subscribeSuccess = true
      console.log('Suscripcion al Topic - Respuesta:', message.payload.toString())
    })
  }

  // Desuscribirse de un Topic
  doUnSubscribe() {
    this.curSubscription?.unsubscribe()
    this.subscribeSuccess = false
  }

  // Publicar un Topic
  doPublish(action: string) {
    console.log("action", action)
    this.publish.payload = action

    const { topic, qos, payload } = this.publish
    console.log(this.publish)

    this.client?.unsafePublish(topic, payload, { qos } as IPublishOptions)
  }

  // Terminar Conexion con el Broker 
  destroyConnection() {
    try {
      this.client?.disconnect(true)
      this.isConnection = false
      console.log('¡Desconectado exitosamente!')
    } catch (error: any) {
      console.log('Falló la desconexión', error.toString())
    }
  }
}
