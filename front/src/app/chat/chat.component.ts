import { Component } from '@angular/core';
import { WebSocketSubject } from 'rxjs/webSocket';

@Component({
  selector: 'app-chat',
  templateUrl: './chat.component.html',
  styleUrls: ['./chat.component.css']
})
export class ChatComponent {
  private socket: WebSocketSubject<any>;
  public messages: string[] = [];
  public userMessage: string = '';

  constructor() {
    this.socket = new WebSocketSubject('ws://localhost:9002');

    this.socket.subscribe(
      message => this.messages.push(message),
      err => console.error(err),
      () => console.warn('Finished')
    );
  }

  sendMessage() {
    this.socket.next(this.userMessage);
    this.userMessage = '';
  }

  ngOnDestroy() {
    this.socket.complete();
  }
}
