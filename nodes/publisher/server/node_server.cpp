#include <iostream>

#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "node_server.hpp"

namespace Nodes {

NodeServer::NodeServer(const std::string& address)
  : address_(address) {
  std::cout << "Nodes::NodeServer[" << reinterpret_cast<uint64_t>(this) << "].address_ = " << address_ << std::endl;
}

grpc::Status NodeServer::sendJSON(grpc::ServerContext* context, const NodesAPI::Publisher::JSON* request, NodesAPI::Publisher::JSON* response) {
  std::cout << "Nodes::NodeServer[" << reinterpret_cast<uint64_t>(this) << "].sendJSON -> " << request->payload() << std::endl;

  response->set_payload("Hello Client!");

  return grpc::Status::OK;
}

void NodeServer::run() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
  builder.RegisterService(this);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}

} // namespace Nodes
