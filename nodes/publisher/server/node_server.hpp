#pragma once

#include <string>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/server.h>

#include "publisher.grpc.pb.h"

namespace Nodes {

class NodeServer : NodesAPI::Publisher::PublisherNode::Service {
  public:
    explicit NodeServer(const std::string& address);

    grpc::Status sendJSON(grpc::ServerContext* context, const NodesAPI::Publisher::JSON* request, NodesAPI::Publisher::JSON* response) override;

    void run();
  private:
    std::string address_;
};

} // namespace Nodes
