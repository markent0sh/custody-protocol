#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "publisher.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using NodesAPI::Publisher::PublisherNode;
using NodesAPI::Publisher::JSON;

class PubClient {
  public:
    PubClient(std::shared_ptr<Channel> channel, const std::string& address)
      : stub_(PublisherNode::NewStub(channel)),
        address_(address) {}

    void SendMessage() {
      ClientContext context;
      JSON request_json;
      JSON response_json;
      request_json.set_payload("Hello Server!");

      Status status = stub_->sendJSON(&context, request_json, &response_json);

      std::cout << response_json.payload() << std::endl;
    }

  private:
    std::unique_ptr<PublisherNode::Stub> stub_;
    std::string address_;
};

int main() {
  PubClient client(grpc::CreateChannel("127.0.0.1:50505", grpc::InsecureChannelCredentials()), "123");

  client.SendMessage();
  return 0;
}
