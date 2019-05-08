//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once
#include <SubgraphView.hpp>

namespace armnn
{
class OptimizationViews
{
public:
    OptimizationViews() = default;

    struct SubstitutionPair
    {
        /// Subgraph of Layers from the original graph which should be replaced
        SubgraphView m_SubstitutableSubgraph;

        /// A subgraph of new layers which will replace layers in m_SubstitutableSubgraph
        SubgraphView m_ReplacementSubgraph;
    };

    using Subgraphs = std::vector<SubgraphView>;
    using Substitutions = std::vector<SubstitutionPair>;

    void AddSubstituion(SubstitutionPair&& substitution)
    {
        m_SuccesfulOptimizations.emplace_back(substitution);
    }

    void AddFailedSubgraph(SubgraphView&& subgraph)
    {
        m_FailedOptimizations.emplace_back(subgraph);
    }

    void AddUntouchedSubgraph(SubgraphView&& subgraph)
    {
        m_UntouchedSubgraphs.emplace_back(subgraph);
    }

    Substitutions GetSubstitutions() const { return m_SuccesfulOptimizations; }
    Subgraphs GetFailedSubgraphs() const { return m_FailedOptimizations; }
    Subgraphs GetUntouchedSubgraphs() const { return m_UntouchedSubgraphs; }
    bool Validate(const SubgraphView& originalSubgraph) const;

private:
    Substitutions m_SuccesfulOptimizations;     ///< Proposed substitutions from successful optimizations
    Subgraphs m_FailedOptimizations;            ///< Subgraphs from the original subgraph which cannot be supported
    Subgraphs m_UntouchedSubgraphs;             ///< Subgraphs from the original subgraph which remain unmodified
};
} //namespace armnn