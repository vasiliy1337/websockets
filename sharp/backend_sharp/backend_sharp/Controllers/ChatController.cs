using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.SignalR;

namespace WebSocket_Sharp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ChatController : ControllerBase
    {
        private readonly IHubContext<ChatHub> hubContext;

        public ChatController(IHubContext<ChatHub> hubContext)
        {
            this.hubContext = hubContext;
        }

        [HttpPost]
        public async Task SendMessage(ChatMessage message)
        {
            await hubContext.Clients.All.SendAsync("messageReceivedFromApi", message);
        }
    }
}
